#ifndef SHOEMANAGERNAMESPACE_H
#define SHOEMANAGERNAMESPACE_H

#include "shoemanagercore_global.h"

namespace ShoeManager {

typedef enum ShoeMessageType
{
    PacketType_Login            = 0x01, // 登录
    PacketType_Login_Disallow   = 0x44, // 禁止
    PacketType_HearBeat         = 0x08, // 心跳包
    PacketType_WifiPosition     = 0x69, // wifi定位
    PacketType_Position         = 0x17, // 定位
    PacketType_UpdateTime       = 0x30, // 更新时间
    PacektType_SyncSetting      = 0x57, // 同步设置
    PacketType_GPS              = 0x10, // GPS

    PacketType_Status           = 0x13, // 状态
    PacketType_String           = 0x15, // 字符串
    PacketType_GPSStatus        = 0x16, // GPS与状态
    PacketType_Server           = 0x80, // 服务器发给定位器

    PacketType_Count

}ShoeMessageType;

SHOEMANAGERCORESHARED_EXPORT QString shoeMessageTypeString(ShoeMessageType type);

enum
{
    TCPSERVER_PORT    = 7008,    // 服务器监听端口
    WAIT_CONNECT_TIMEOUT = 3000, // 连接服务器超时时间
    CONNECT_TRY_TIMES = 1,       // 连接尝试次数
    HEARTBEAT_INTERVAL = 5*60*1000, // 5分钟
};

}

#endif // SHOEMANAGERNAMESPACE_H
