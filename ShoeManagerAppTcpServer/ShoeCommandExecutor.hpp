#ifndef SHOESERVER_H
#define SHOESERVER_H

#include <QString>
#include <QMap>
#include <QTimer>
#include <QDateTime>

#include "ShoeManagerTcpServer.hpp"
#include "ShoeManagerNamespace.h"
using namespace ShoeManager;

class ShoeCommandExecutor : public QObject
{
    Q_OBJECT

public:
    explicit ShoeCommandExecutor(QObject *parent = 0);
    ~ShoeCommandExecutor();

    bool initServer();
    bool finalize();

private slots:
    void slotDisconnected(const int nDescriptor);
    void slotPacketReceived(const ShoeMessagePacket& packet, const int nDescriptor);

private:
    void receiveLogin(const int nDescriptor, QByteArray content);
    void receiveUpdateTime(const int nDescriptor, QByteArray content);
    void receiveStatus(const int nDescriptor, QByteArray content);
    void receiveHearBeat(const int nDescriptor, QByteArray content);
    void receiveGPS(const int nDescriptor, QByteArray content);
    void receivePosition(const int nDescriptor, QByteArray content);
    void receiveWifiPosition(const int nDescriptor, QByteArray content);

private:
    ShoeManagerTcpServer *commServer;
    QMap<int, QString> mDescriptorIMEI;
};


#endif // SHOESERVER_H
