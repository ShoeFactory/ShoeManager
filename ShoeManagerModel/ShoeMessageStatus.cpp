#include "ShoeMessageStatus.hpp"
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
