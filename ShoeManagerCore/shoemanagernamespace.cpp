#include "ShoeManagerNamespace.h"
#include <QString>

QString ShoeManager::shoeMessageTypeString(ShoeManager::ShoeMessageType type)
{
    QString result;

    switch (type) {
    case PacketType_Login:
        result = "PacketType_Login";
        break;
    case PacketType_Login_Disallow:
        result = "PacketType_Login_Disallow";
        break;
    case PacketType_HearBeat:
        result = "PacketType_HearBeat";
        break;
    case PacketType_WifiPosition:
        result = "PacketType_WifiPosition";
        break;
    case PacketType_Position:
        result = "PacketType_Position";
        break;
    case PacketType_UpdateTime:
        result = "PacketType_UpdateTime";
        break;
    case PacektType_SyncSetting:
        result = "PacektType_SyncSetting";
        break;
    case PacketType_GPS:
        result = "PacketType_GPS";
        break;
    case PacketType_Status:
        result = "PacketType_Status";
        break;
    case PacketType_String:
        result = "PacketType_String";
        break;
    case PacketType_GPSStatus:
        result = "PacketType_GPSStatus";
        break;
    case PacketType_Server:
        result = "PacketType_Server";
        break;
    default:
        result = QString::number(int(type));
        break;
    }

    return result;
}
