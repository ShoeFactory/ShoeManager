#include <QJsonValue>
#include <QByteArray>
#include <QDebug>
#include "ShoeCommandExecutor.hpp"

#include "ShoeMessageLogin.h"
#include "ShoeMessageGPS.h"
#include "ShoeMessageStatus.hpp"
#include "ShoeMessageWifiPosition.hpp"

#include "ShoeManagerNetwork.hpp"

ShoeCommandExecutor::ShoeCommandExecutor(QObject *parent) :
    QObject(parent)
{
    commServer = new ShoeManagerTcpServer(this);
    commServer->setHeatBeatInterval(ShoeManager::HEARTBEAT_INTERVAL);

    connect(commServer, &ShoeManagerTcpServer::onListeningStatus, [](bool isListening){
        if(isListening)
            qDebug() << "[启动了]";
        else
            qDebug() << "[停止了]" ;
    });

    connect(commServer, &ShoeManagerTcpServer::onConnected, [](int nDescriptor){
        // 等到接收到登陆的包后才建立context
        qDebug() << "[连接" + QString::number(nDescriptor) + "]";
    });

    connect(commServer, &ShoeManagerTcpServer::onErrorOccurred, [](QString errorString, int nDescriptor){
        qDebug() << "[错误" + QString::number(nDescriptor) + "]" + errorString;
    });

    connect(commServer, &ShoeManagerTcpServer::onPacketSend, [](const ShoeMessagePacket &packet, const int nDescriptor){
        qDebug() << "[发送" + QString::number(nDescriptor) + "] <" + ShoeManager::shoeMessageTypeString(packet.msgType) + "> : " + packet.msgContent.toHex();
    });

    connect(commServer, &ShoeManagerTcpServer::onDisconnected, this, &ShoeCommandExecutor::slotDisconnected);
    connect(commServer, &ShoeManagerTcpServer::onPacketReceived, this, &ShoeCommandExecutor::slotPacketReceived);
}

ShoeCommandExecutor::~ShoeCommandExecutor()
{
    finalize();
}

bool ShoeCommandExecutor::initServer()
{
    return commServer->initialize(ShoeManager::TCPSERVER_PORT);
}

bool ShoeCommandExecutor::finalize()
{
    return commServer->finalize();
}

void ShoeCommandExecutor::slotDisconnected(const int nDescriptor)
{
    qDebug() << "[断开" + QString::number(nDescriptor) + "]";

    auto imei = mDescriptorIMEI.value(nDescriptor);
    auto *result = ShoeManagerNetwork::getInstance()->setDeviceIsOnline(imei, false);

    connect(result, &ShoeManagerNetworkResult::requestFinished, [=](){
        qDebug() << result->oRequestData["requestUrl"].toString()
                << result->oReturnData << result->oReturnMessage;
    });

    mDescriptorIMEI.remove(nDescriptor);
}

void ShoeCommandExecutor::slotPacketReceived(const ShoeMessagePacket &packet, const int nDescriptor)
{
    qDebug() << "[接收" + QString::number(nDescriptor) + "] <" + ShoeManager::shoeMessageTypeString(packet.msgType) + "> : " + packet.msgContent.toHex();

    ShoeMessageType msgType = packet.msgType;
    QByteArray msgContent = packet.msgContent;

    switch (msgType) {
    case PacketType_Login:
        receiveLogin(nDescriptor, msgContent);
        break;
    case PacketType_UpdateTime:
        receiveUpdateTime(nDescriptor, msgContent);
        break;
    case PacketType_Status:
        receiveStatus(nDescriptor, msgContent);
        break;
    case PacketType_HearBeat:
        receiveHearBeat(nDescriptor, msgContent);
        break;
    case PacketType_GPS:
        receiveGPS(nDescriptor, msgContent);
        break;
    case PacketType_Position:
        receivePosition(nDescriptor, msgContent);
        break;
    case PacketType_WifiPosition:
        receiveWifiPosition(nDescriptor, msgContent);
        break;
    default:
        break;
    }
}

void ShoeCommandExecutor::receiveLogin(const int nDescriptor, QByteArray content)
{
    ShoeMessageLogin loginReceived;
    loginReceived.parseData(content);

    ShoeMessagePacket packet;
    packet.msgType = PacketType_Login;
    packet.msgContent = QByteArray();
    commServer->sendPacket(packet, nDescriptor);

    QString IMEI = loginReceived.getIMEI();
    mDescriptorIMEI.insert(nDescriptor, IMEI);

    auto *result = ShoeManagerNetwork::getInstance()->setDeviceIsOnline(IMEI, true);

    connect(result, &ShoeManagerNetworkResult::requestFinished, [=](){
        qDebug() << "imei" << IMEI;
        qDebug() << result->oRequestData["requestUrl"].toString()
                << result->oReturnCode << result->oReturnMessage;
    });
}

void ShoeCommandExecutor::receiveUpdateTime(const int nDescriptor, QByteArray content)
{
    Q_UNUSED(content)

    // 7878 07 30 E00705053718 0D0A GMT 时间
    // E00705053718 ==> 16年7月5日5点55分24秒
    QDateTime datetime = QDateTime::currentDateTimeUtc();
    QString dateTimeString = datetime.toString("yyyyMMddhhmmss");
    dateTimeString.remove(0, 2);
    QByteArray dateTimeByteArray = QByteArray::fromHex(dateTimeString.toUtf8());

    ShoeMessagePacket packet;
    packet.msgType = PacketType_UpdateTime;
    packet.msgContent = dateTimeByteArray;
    commServer->sendPacket(packet, nDescriptor);
}

void ShoeCommandExecutor::receiveStatus(const int nDescriptor, QByteArray content)
{
    auto imei = mDescriptorIMEI.value(nDescriptor);

    ShoeMessageStatus status;
    status.parseData(content);

    auto *result = ShoeManagerNetwork::getInstance()->setDevicePower(imei, status.power);

    connect(result, &ShoeManagerNetworkResult::requestFinished, [=](){
        qDebug() << result->oRequestData["requestUrl"].toString()
                << result->oReturnCode << result->oReturnMessage;
    });
}

void ShoeCommandExecutor::receiveHearBeat(const int nDescriptor, QByteArray content)
{
    Q_UNUSED(content)
    commServer->heartBeat(nDescriptor);
}

void ShoeCommandExecutor::receiveGPS(const int nDescriptor, QByteArray content)
{
    auto imei = mDescriptorIMEI.value(nDescriptor);

    ShoeMessageGPS gps;
    gps.parseData(content);

    auto *result = ShoeManagerNetwork::getInstance()->addDeviceGPS(imei,
                                                                   gps.getObject());

    connect(result, &ShoeManagerNetworkResult::requestFinished, [=](){
        qDebug() << result->oRequestData["requestUrl"].toString()
                << result->oReturnCode << result->oReturnMessage;
    });
}


void ShoeCommandExecutor::receivePosition(const int nDescriptor, QByteArray content)
{
    /*
     * 文档中也没有17这个协议号
     * lbs数据重复太多 不准确
     *
     * 格式和69 WifiPosition一样
     *
     * 目前看来是随着心跳一起传送
     */

    Q_UNUSED(nDescriptor)
    Q_UNUSED(content)
}

void ShoeCommandExecutor::receiveWifiPosition(const int nDescriptor, QByteArray content)
{
    // 1. wifi/lbs 2.lbs 第二种情况wifi热点无
    auto imei = mDescriptorIMEI.value(nDescriptor);

    ShoeMessageWifiPosition wifiPosition;
    wifiPosition.parseData(content);

    qDebug() << "==========WifiPosition========";
    qDebug() << wifiPosition.jsonString();

    auto *result = ShoeManagerNetwork::getInstance()->addDeviceWifiLBS(imei,
                                                                      wifiPosition.getObject());

    connect(result, &ShoeManagerNetworkResult::requestFinished, [=](){
        qDebug() << result->oRequestData["requestUrl"].toString()
                << result->oReturnCode << result->oReturnMessage;
    });
}


