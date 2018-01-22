#ifndef SHOEMANAGERTCPSERVERPRIVATE_HPP
#define SHOEMANAGERTCPSERVERPRIVATE_HPP

#include <ShoeManagerTcpServer.hpp>
#include <QTcpServer>
#include <QDateTime>
#include <QTimer>

class ShoeManagerTcpServerPrivate : public QTcpServer
{
    Q_OBJECT

    struct TcpContext{
        QDateTime bindTime; // 建立连接的时间
        QDateTime lastTime; // 最后heatBeat
    };

public:
    ShoeManagerTcpServerPrivate(ShoeManagerTcpServer* q);

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
    /**< 客户Socket管理链表 >**/
    QList<ShoeTcpSocket*> m_socketList;
    QMap<int, TcpContext> mDescriptorContext;

protected:
    void incomingConnection(qintptr nSocketDescriptor) override;

private slots:
    void slotSocketDisconnected(const int nDescriptor);

private slots:
    void slotCheckHeartBeat();
private:
    QTimer *mTimerCheckHeartBeat;
    int mHeartBeatIntervalSecs;

private:
    ShoeManagerTcpServer *q_ptr;
};

#endif // SHOEMANAGERTCPSERVERPRIVATE_HPP
