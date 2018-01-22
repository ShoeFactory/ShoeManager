#include <QHostAddress>
#include "ShoeManagerTcpServer.hpp"
#include "ShoeManagerTcpServerPrivate.hpp"

ShoeManagerTcpServer::ShoeManagerTcpServer(QObject *parent)
    : QObject(parent)
{
    d_ptr = new ShoeManagerTcpServerPrivate(this);

    connect(d_ptr, &ShoeManagerTcpServerPrivate::onListeningStatus, this, &ShoeManagerTcpServer::onListeningStatus);
    connect(d_ptr, &ShoeManagerTcpServerPrivate::onConnected, this, &ShoeManagerTcpServer::onConnected);
    connect(d_ptr, &ShoeManagerTcpServerPrivate::onDisconnected, this, &ShoeManagerTcpServer::onDisconnected);
    connect(d_ptr, &ShoeManagerTcpServerPrivate::onPacketReceived, this, &ShoeManagerTcpServer::onPacketReceived);
    connect(d_ptr, &ShoeManagerTcpServerPrivate::onPacketSend, this, &ShoeManagerTcpServer::onPacketSend);
    connect(d_ptr, &ShoeManagerTcpServerPrivate::onErrorOccurred, this, &ShoeManagerTcpServer::onErrorOccurred);
}

ShoeManagerTcpServer::~ShoeManagerTcpServer()
{
    delete d_ptr;
}

bool ShoeManagerTcpServer::initialize(int port)
{
    return d_ptr->initialize(port);
}

bool ShoeManagerTcpServer::finalize()
{
    return d_ptr->finalize();
}

bool ShoeManagerTcpServer::sendPacket(const ShoeMessagePacket &packet, const int nDescriptor)
{
   return d_ptr->sendPacket(packet, nDescriptor);
}

void ShoeManagerTcpServer::setHeatBeatInterval(const int secs)
{
    d_ptr->setHeatBeatInterval(secs);
}

void ShoeManagerTcpServer::heartBeat(const int nDescriptor)
{
    d_ptr->heartBeat(nDescriptor);
}

void ShoeManagerTcpServer::closeSocket(int nDescriptor)
{
   d_ptr->closeSocket(nDescriptor);
}
