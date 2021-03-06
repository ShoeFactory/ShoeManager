﻿#include "ShoeMessageStatus.hpp"
#include <QByteArray>

#include <QDebug>

void ShoeMessageStatus::parseData(QByteArray data)
{
    if(data.length() == 5)
    {
        messageType = data[0];
        power = data[1];
        firmwareVersion = data[2];
        timearea = data[3];
        timeInterval = data[4];
    }

    if(data.length() == 6)
    {
        messageType = data[1];
        power = data[2];
        firmwareVersion = data[3];
        timearea = data[4];
        timeInterval = data[5];
    }

    if(data.length() == 7)
    {
        messageType = data[1];
        power = data[2];
        firmwareVersion = data[3];
        timearea = data[4];
        timeInterval = data[5];
    }

}

QJsonObject ShoeMessageStatus::getObject()
{
    QJsonObject oJsonData = {
        {"messageType", messageType},
        {"power", power},
        {"firmwareVersion", firmwareVersion},
        {"timearea", firmwareVersion},
        {"timeInterval", timeInterval}
    };
    return oJsonData;
}
