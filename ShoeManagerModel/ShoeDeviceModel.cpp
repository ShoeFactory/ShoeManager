#include "ShoeDeviceModel.hpp"
#include <QJsonObject>
#include <QJsonArray>

// 编辑设备 新绑定解除绑定时有用到
void parseJson(QList<ShoeDeviceModel> &result, QJsonValue value)
{
    QJsonObject object = value.toObject();
    QJsonArray deviceArray = object["devices"].toArray();

    foreach (QJsonValue deviceValue, deviceArray) {

        ShoeDeviceModel device;

        QJsonObject deviceObject = deviceValue.toObject();
        device.name = deviceObject["name"].toString();
        device.imei = deviceObject["sid"].toString();
        device.isOnline = deviceObject["isOnline"].toBool();
        device.powerPercent = deviceObject["power"].toDouble();
        device.isSubscribed = deviceObject["isSubscribed"].toBool();

        result.append(device);
    }
}

bool ShoeDeviceModel::operator==(const ShoeDeviceModel &model)
{
    return this->imei == model.imei;
}

bool ShoeDeviceModel::operator <(const ShoeDeviceModel &model)
{
    return this->imei < model.imei;
}
