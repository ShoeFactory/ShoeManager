#include "ShoeManagerTcpServerPrivate.hpp"
#include <QDateTime>

ShoeManagerTcpServerPrivate::ShoeManagerTcpServerPrivate(ShoeManagerTcpServer *q)
    : q_ptr(q)
{
    mTimerCheckHeartBeat = new QTimer;
    connect(mTimerCheckHeartBeat, &QTimer::timeout, this, &ShoeManagerTcpServerPrivate::slotCheckHeartBeat);
}

bool ShoeManagerTcpServerPrivate::initialize(int port)
{
    bool bRet(false);

    do
    {
        // 在指定的端口对任意地址进行监听
        if (!listen(QHostAddress::Any, port))
        {
            break;
        }

        bRet = true;
        emit onListeningStatus(true);
    } while(false);

    return bRet;
}

bool ShoeManagerTcpServerPrivate::finalize()
{
    if ( isListening() )
    {
        // 不在监听新连接
        close();

        // 关闭现有的连接
        foreach (ShoeTcpSocket *socket, m_socketList)
        {
            socket->close();
        }

        emit onListeningStatus(false);
    }
    return true;
}

void ShoeManagerTcpServerPrivate::closeSocket(int nDescriptor)
{
    QList<ShoeTcpSocket*>::iterator it;

    for(it=m_socketList.begin(); it!=m_socketList.end(); it++)
    {
        ShoeTcpSocket* item = *it;

        if ( nDescriptor == item->socketDescriptor())
        {
            item->abort();
        }
    }
}

bool ShoeManagerTcpServerPrivate::sendPacket(const ShoeMessagePacket &packet, const int nDescriptor)
{
    QList<ShoeTcpSocket*>::iterator it;

    for(it=m_socketList.begin(); it!=m_socketList.end(); it++)
    {
        ShoeTcpSocket* item = *it;

        if ( nDescriptor == item->socketDescriptor())
        {
            return item->sendPacket(packet);
        }
    }

    return false;
}

void ShoeManagerTcpServerPrivate::setHeatBeatInterval(const int secs)
{
    mHeartBeatIntervalSecs = secs;
    mTimerCheckHeartBeat->start(secs * 1000);
}

void ShoeManagerTcpServerPrivate::heartBeat(const int nDescriptor)
{
    auto &context = mDescriptorContext[nDescriptor];
    context.lastTime = QDateTime::currentDateTime();
}

void ShoeManagerTcpServerPrivate::incomingConnection(qintptr nSocketDescriptor)
{
    // 创建一个新的Socket与客户端通信
    ShoeTcpSocket* socket = new ShoeTcpSocket(this);
    socket->setSocketID(nSocketDescriptor);
    socket->setSocketDescriptor(nSocketDescriptor);

    connect(socket, SIGNAL(onConnected(int)), this, SIGNAL(onConnected(int)));
    connect(socket, SIGNAL(onDisonnected(int)), this, SLOT(slotSocketDisconnected(int)));
    connect(socket, SIGNAL(onPacketSend(ShoeMessagePacket,int)), this, SIGNAL(onPacketSend(ShoeMessagePacket, int)));
    connect(socket, SIGNAL(onPacketReceived(ShoeMessagePacket, int)), this, SIGNAL(onPacketReceived(ShoeMessagePacket,int)));
    connect(socket, SIGNAL(onErrorOccurred(QString, int)), this, SIGNAL(onErrorOccurred(QString,int)));

    // 高调显示 新的连接产生了
    emit socket->onConnected(nSocketDescriptor);

    // 加入客户端套接字列表以便管理
    m_socketList.append(socket);
    TcpContext context;
    context.bindTime = QDateTime::currentDateTime();
    context.lastTime = QDateTime::currentDateTime();
    mDescriptorContext.insert(nSocketDescriptor, context);
}

void ShoeManagerTcpServerPrivate::slotSocketDisconnected(const int nDescriptor)
{
    ShoeTcpSocket* socket = qobject_cast<ShoeTcpSocket*>(sender());

    if(socket)
    {
        m_socketList.removeOne(socket);
        socket->deleteLater();
    }

    emit onDisconnected(nDescriptor);
}

void ShoeManagerTcpServerPrivate::slotCheckHeartBeat()
{
    // 占用资源不放 服务器出面给断开
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QMap<int, TcpContext>::iterator it;
    for(it = mDescriptorContext.begin(); it!=mDescriptorContext.end();it++)
    {
        TcpContext context = it.value();
        if(context.lastTime.secsTo(currentDateTime) > mHeartBeatIntervalSecs)
        {
            closeSocket(it.key());
        }
    }
}
