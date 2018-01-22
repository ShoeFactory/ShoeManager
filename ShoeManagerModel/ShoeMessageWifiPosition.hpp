#ifndef SHOEMESSAGEWIFIPOSITION_HPP
#define SHOEMESSAGEWIFIPOSITION_HPP

#include "shoemanagermodel_global.h"

#include <QList>
#include <QDataStream>

class  WifiData{
public:
    // 16进制
    QString bssid;
    QString rssi;
};
QDataStream &operator>>(QDataStream &in, WifiData &data);

class BCDDateTime{
public:
    QString dateTime;
};
QDataStream &operator>>(QDataStream &in, BCDDateTime &data);


class LBSData{
public:
    // 16进制
    QString lac;
    QString mciss;
    QString cellid;
};
QDataStream &operator>>(QDataStream &in, LBSData &data);

class MCCMNC{
public:
    // 10进制
    QString mcc;
    QString mnc;
};
QDataStream &operator>>(QDataStream &in, MCCMNC &data);


class SHOEMANAGERMODELSHARED_EXPORT ShoeMessageWifiPosition
{
public:

    QList<WifiData> wifiDataList;
    QList<LBSData>  lbsDataList;
    BCDDateTime dateTime;
    MCCMNC mccnc;

    void parseData(QByteArray data);
    QJsonObject getObject();

    QString jsonString();
};

#endif // SHOEMESSAGEWIFIPOSITION_HPP
