#include "ShoeManagerTcpClient.hpp"

ShoeManagerTcpClient::ShoeManagerTcpClient(QObject *parent)
    :QObject(parent)
{

}

bool ShoeManagerTcpClient::initialize(QHostAddress address, int port)
{
    bool bRet(false);

    do
    {
        m_socket = new ShoeTcpSocket(this);

        connect(m_socket, SIGNAL(onConnected(int)), this, SIGNAL(onConnected()));
        connect(m_socket, SIGNAL(onDisonnected(int)), this, SIGNAL(onDisconnected()));
        connect(m_socket, SIGNAL(onPacketReceived(ShoeMessagePacket, int)), this, SIGNAL(onPacketReceived(ShoeMessagePacket)));
        connect(m_socket, SIGNAL(onPacketSend(ShoeMessagePacket,int)), this, SIGNAL(onPacketSend(ShoeMessagePacket)));
        connect(m_socket, SIGNAL(onErrorOccurred(QString, int)), this, SIGNAL(onErrorOccurred(QString)));

        bool bConnected(false);

        for (int i=0; i<CONNECT_TRY_TIMES; i++)
        {
            // 与Tcp服务器连接，连接成功后发出connected信号
            m_socket->connectToHost(address, port);

            if (!m_socket->waitForConnected(WAIT_CONNECT_TIMEOUT))
            {
               // ShoeUtilsLibrary::DebugTimeString("wait for connect timeout");
                continue;
            }
            else
            {
                bConnected = true;
                break;
            }

        }

        if (!bConnected)
        {
            break;
        }

        bRet = true;
    } while(false);

    return bRet;
}

bool ShoeManagerTcpClient::finalize()
{
    bool bRet(false);

    do
    {
        m_socket->disconnectFromHost();

        bRet = (m_socket->state() == QAbstractSocket::UnconnectedState ||
                m_socket->waitForDisconnected());
    } while(false);

    return bRet;
}

bool ShoeManagerTcpClient::sendPacket(const ShoeMessagePacket &packet)
{
    return m_socket->sendPacket(packet);
}
