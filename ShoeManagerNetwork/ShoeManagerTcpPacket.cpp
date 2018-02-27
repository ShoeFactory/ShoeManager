#include "ShoeManagerTcpPacket.hpp"
#include <QList>

ShoeTcpPacket ShoeTcpPacket::fromShoeMassagePacket(const ShoeMessagePacket &packet)
{
    ShoeTcpPacket result;

    result.start = 0x7878;
    result.stop  = 0x0D0A;

    result.msgType    = qint8(packet.msgType);
    result.msgContent = packet.msgContent;

    // 长度 = 协议号+内容 协议号一般是1个字节
    result.length = (quint8) (result.msgContent.size() + 1);

    return result;
}

ShoeMessagePacket ShoeMessagePacket::fromShoeTcpPacket(const ShoeTcpPacket &wrappedPacket)
{
    ShoeMessagePacket result;
    result.msgContent = wrappedPacket.msgContent;
    result.msgType = ShoeMessageType(wrappedPacket.msgType);
    return result;
}

QDataStream &operator <<(QDataStream &stream, const ShoeTcpPacket &packet)
{
    stream << packet.start;

    stream << packet.length;
    stream << packet.msgType;

    int contentLength = packet.msgContent.size();
    for(int i=0; i<contentLength; i++)
    {
        qint8 temp =  packet.msgContent.at(i);
        stream << temp;
    }

    stream << packet.stop;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, ShoeTcpPacket &packet)
{
    stream >> packet.start;
    stream >> packet.length;

    // 协议号
    stream >> packet.msgType;

    // 内容长度 = 长度 - 协议号长度
    int contentLength = packet.length-1;
    QByteArray content;
    content.resize(contentLength);
    for(int i=0; i<contentLength; i++)
    {
        qint8 temp;
        stream >> temp;
        content[i] = temp;
    }
    packet.msgContent = content;

    stream >> packet.stop;
    return stream;
}
