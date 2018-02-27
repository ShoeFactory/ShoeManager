#ifndef SHOEDEVICEMODEL_HPP
#define SHOEDEVICEMODEL_HPP

#include <QObject>
#include <QString>
#include "shoemanagermodel_global.h"


struct SHOEMANAGERMODELSHARED_EXPORT ShoeDeviceModel{
    QString name;
    bool isOnline = false;
    bool isSubscribed = false;
    double powerPercent = 0.0;
    QString imei;

    bool operator==(const ShoeDeviceModel &model);
    bool operator <(const ShoeDeviceModel &model);
};

SHOEMANAGERMODELSHARED_EXPORT void parseJson(QList<ShoeDeviceModel> &result, QJsonValue value);

#endif // SHOEDEVICEMODEL_HPP
