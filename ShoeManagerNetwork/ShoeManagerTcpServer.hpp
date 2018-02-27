#ifndef SHOETCPSERVER_H
#define SHOETCPSERVER_H

#include "ShoeManagerTcpSocket.hpp"
#include "shoemanagernetwork_global.h"
class ShoeManagerTcpServerPrivate;

class SHOEMANAGERNETWORKSHARED_EXPORT ShoeManagerTcpServer:public QObject
{
    Q_OBJECT
public:
    ShoeManagerTcpServer(QObject* parent=NULL);
    ~ShoeManagerTcpServer();

public:
    bool initialize(int port);
    bool finalize();
    void closeSocket(int nDescriptor);
    bool sendPacket(const ShoeMessagePacket& packet, const int nDescriptor);
    void setHeatBeatInterval(const int secs);
    void heartBeat(const int nDescriptor);

signals:
    void onListeningStatus(bool isListening);
    void onConnected(const int nDescriptor);
    void onDisconnected(const int nDescriptor);
    void onPacketReceived(const ShoeMessagePacket& packet, const int nDescriptor);
    void onPacketSend(const ShoeMessagePacket& packet, const int nDescriptor);
    void onErrorOccurred(const QString& errorString, const int nDescriptor);

private:
    ShoeManagerTcpServerPrivate *d_ptr;
};

#endif // SHOETCPSERVER_H
