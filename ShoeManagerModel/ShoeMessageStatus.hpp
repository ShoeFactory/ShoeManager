#ifndef MESSAGESTATUS_HPP
#define MESSAGESTATUS_HPP

#include "shoemanagermodel_global.h"

class SHOEMANAGERMODELSHARED_EXPORT ShoeMessageStatus
{
public:
    qint8 messageType;      // 协议号
    qint8 power;            // 电量
    qint8 firmwareVersion;  // 软件版本
    qint8 timearea;         // 时区
    qint8 timeInterval;     // 时间间隔

    void parseData(QByteArray data);
    QJsonObject getObject();
};

#endif // MESSAGESTATUS_HPP
