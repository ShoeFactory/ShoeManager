#ifndef SHOETCPCLIENT_H
#define SHOETCPCLIENT_H

#include <QHostAddress>
#include <QTcpSocket>
#include <QObject>

#include "shoemanagernetwork_global.h"
#include "ShoeManagerTcpSocket.hpp"

class SHOEMANAGERNETWORKSHARED_EXPORT ShoeManagerTcpClient : public QObject
{
    Q_OBJECT
public:
    ShoeManagerTcpClient(QObject * parent=NULL);
    bool initialize(QHostAddress address, int port);
    bool finalize();

    bool sendPacket(const ShoeMessagePacket& packet);

signals:
    void onConnected();
    void onDisconnected();
    void onPacketSend(const ShoeMessagePacket& ShoeMessagePacket);
    void onPacketReceived(const ShoeMessagePacket& packet);
    void onErrorOccurred(const QString& errorString);

private:
    ShoeTcpSocket* m_socket;
};

#endif // SHOETCPCLIENT_H
