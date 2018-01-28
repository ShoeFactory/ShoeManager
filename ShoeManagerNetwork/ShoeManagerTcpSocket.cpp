#include "ShoeManagerTcpSocket.hpp"

ShoeTcpSocket::ShoeTcpSocket(QObject *parent)
    :QTcpSocket(parent)
{
    connect(this, &QAbstractSocket::connected, this, &ShoeTcpSocket::slotConnected);
    connect(this, &QAbstractSocket::disconnected, this, &ShoeTcpSocket::slotDisconnected);
    connect(this, &QIODevice::readyRead, this, &ShoeTcpSocket::slotDataReceived);
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotErrorOccurred(QAbstractSocket::SocketError)));
}

void ShoeTcpSocket::setSocketID(const int nDescriptor)
{
    this->socketID = nDescriptor;
}

bool ShoeTcpSocket::sendPacket(const ShoeMessagePacket &packet)
{
    return sendRule(packet);
}

bool ShoeTcpSocket::sendRule(const ShoeMessagePacket &packet)
{
    bool bRet(false);

    do
    {
        // 将Packet转换成WrappedPacket
        ShoeTcpPacket tcpPacket = ShoeTcpPacket::fromShoeMassagePacket(packet);

        // 将WrappedPacket转换成ByteArray
        QByteArray sendByte;
        QDataStream out(&sendByte, QIODevice::WriteOnly);
        out << tcpPacket;

        // 开始发送网络字节
        qint64 sendLen = write(sendByte);
        Q_UNUSED(sendLen)

        // 等待写入完成
        if (!waitForBytesWritten())
        {
            qCritical() << "client write bytes to socket failed.";
            break;
        }

//        // 检验是否完整发送
//        if (sendLen < (qint64)(wrappedPacket.length + 5))
//        {
//            qCritical() << "client write bytes to socket failed.";
//            break;
//        }

        bRet = true;
    } while(false);

    // 通知外界已发送
    if(bRet)
        emit onPacketSend(packet, socketDescriptor());

    return bRet;
}

void ShoeTcpSocket::receiveRule(QByteArray &recvBuffer)
{
    while(true)
    {
        int totalLen = recvBuffer.size();

        //不够包头的数据直接就不处理。
        if( totalLen < (int)(sizeof(quint16) + sizeof(quint8))  )
        {
            break;
        }

        //与QDataStream绑定，方便操作。
        QDataStream in(recvBuffer);

        // 找结束点
        int stopPosition = recvBuffer.indexOf(QByteArray::fromHex("0d0a"));
        qDebug()<<"recvBuffer "<< recvBuffer.toHex() << stopPosition;
        // 78 78 0d 01 03 56 31 40 41 40 67 41 35 0d0a  13
        // 78 78 01 08 0d0a  4

        // 78 78 0a 01 01 23 45 67 89 01 23 45 35 0d0a  13

        // 没找到 退出
        if(stopPosition == -1)
        {
            break;
        }

        // Todo 这里需要健全一下 长度的问题？

        //数据包已收够，进行解析
        ShoeTcpPacket tcpPacket;
        in.device()->seek(0);

        // 去除头
        in >> tcpPacket.start;
        in >> tcpPacket.length;
        in >> tcpPacket.msgType;

        /*
         *  0x780x78+数据长度+协议号+数据内容+0x0d0x0a
         *          数据长度=(协议号+数据内容)的值为数
         *  特殊几条不是这个规则的在协议详细内容中有相应说明
         */
        int dataLength = stopPosition - sizeof(qint8) * 3;

        QByteArray content;
        // 正常包
        if(dataLength == tcpPacket.length)
        {
            int contentLength = dataLength - sizeof(qint8);
            for(int i=0; i<contentLength; i++)
            {
                qint8 temp;
                in >> temp;
                content.append(temp);
            }
        }

        else
        {
            in.device()->seek(2);
            for(int i=0; i<stopPosition-2; i++)
            {
                qint8 temp;
                in >> temp;
                content.append(temp);
            }
        }
        tcpPacket.msgContent = content;

        in >> tcpPacket.stop;

        // 通知外界已接收
        emit onPacketReceived(ShoeMessagePacket::fromShoeTcpPacket(tcpPacket), socketDescriptor());

        //用多余的数据更新缓存
        recvBuffer = recvBuffer.right(totalLen - (stopPosition+2));
    }
}

void ShoeTcpSocket::slotConnected()
{
    setSocketID(socketDescriptor());
    emit onConnected(socketID);
}

void ShoeTcpSocket::slotDisconnected()
{
    emit onDisonnected(socketID);
}

void ShoeTcpSocket::slotDataReceived()
{
    if ( bytesAvailable() <= 0 )
    {
        return;
    }

    //临时获得从缓存区取出来的数据，但是不确定每次取出来的是多少。
    QByteArray buffer = readAll();

    // ShoeUtilsLibrary::DebugTimeString(buffer.toHex());

    //上次缓存加上这次数据
    recvBuffer.append(buffer);

    //要是扩展的话 扩展这个就行
    receiveRule(recvBuffer);
}

void ShoeTcpSocket::slotErrorOccurred(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error);
    QString errorString = this->errorString();
    emit onErrorOccurred(errorString, socketID);
}
