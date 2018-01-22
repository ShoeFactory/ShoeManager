#ifndef SHOEMANAGERTCPPACKET_HPP
#define SHOEMANAGERTCPPACKET_HPP

#include <QByteArray>
#include <QDataStream>

#include "ShoeManagerNamespace.h"
using namespace ShoeManager;


/**
 * 数据包 上层运用
 */
struct ShoeTcpPacket;
struct ShoeMessagePacket
{
    ShoeMessageType msgType;    // 包类型
    QByteArray msgContent;      // 包内容为特定字节

    static ShoeMessagePacket fromShoeTcpPacket(const ShoeTcpPacket& wrappedPacket);
};


struct ShoeTcpPacket
{
    qint16      start;          //  起始位   2
    quint8      length;         //  长度     1
    qint8       msgType;        //  包类型   1
    QByteArray  msgContent;     //  包内容   N
    qint16      stop;           //  停止位   2

    static ShoeTcpPacket fromShoeMassagePacket(const ShoeMessagePacket& packet);
};

QDataStream& operator << (QDataStream& stream, const ShoeTcpPacket& packet);
QDataStream& operator >> (QDataStream& stream, ShoeTcpPacket& packet);

#endif // SHOEMANAGERTCPPACKET_HPP
