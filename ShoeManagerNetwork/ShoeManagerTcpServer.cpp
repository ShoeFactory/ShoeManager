#include <QHostAddress>
#include "ShoeManagerTcpServer.hpp"
#include "ShoeManagerTcpServerPrivate.hpp"

ShoeManagerTcpServer::ShoeManagerTcpServer(QObject *parent)
    : QObject(parent)
{
    d_ptr = new ShoeManagerTcpServerPrivate(this);
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
