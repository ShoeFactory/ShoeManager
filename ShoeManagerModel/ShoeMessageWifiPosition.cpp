#include "ShoeMessageWifiPosition.hpp"
#include <QDateTime>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

void ShoeMessageWifiPosition::parseData(QByteArray data)
{
    /*
    wifi/lbs
    eg. 7878 03 69 160413031849 1475905BD30E25 001E10BBF7635D 14759006E62656 05 01CC00
    28660F2132 28660F1F28 28660EA81E 2866107314 28660F2014 0D0A

    03 69 160413031849 1475905BD30E25 001E10BBF7635D 14759006E62656 05 01CC00
    28660F2132 28660F1F28 28660EA81E 2866107314 28660F2014

    lbs
    eg. 7878 00 69 160413031849 05 01CC00 28660F2132 28660F1F28 28660EA81E 2866107314 28660F2014 0D0A
    00 69 160413031849 05 01CC00 28660F2132 28660F1F28 28660EA81E 2866107314 28660F2014
    */
    QDataStream in(data);
    qint8 wifiDataCount = 0;
    in >> wifiDataCount;

    qint8 protocalNo = 0x69;
    in >> protocalNo;

    in >> dateTime;

    for(int i=0; i<wifiDataCount; i++)
    {
        WifiData wifiData;
        in >> wifiData;
        wifiDataList.append(wifiData);
    }

    qint8 lbsDataCount = 0;
    in >> lbsDataCount;
    if(lbsDataCount > 0)
    {
        in >> mccnc;

        for(int i=0; i<lbsDataCount; i++)
        {
            LBSData lbsData;
            in >> lbsData;
            lbsDataList.append(lbsData);
        }
    }
}

QString ShoeMessageWifiPosition::jsonString()
{
    QJsonDocument doc(getObject());
    return doc.toJson(QJsonDocument::Indented);
}

QJsonObject ShoeMessageWifiPosition::getObject()
{
    QJsonObject objectWifiPosition;
    // 1
    objectWifiPosition.insert("dateTime", dateTime.dateTime);

    // 2
    QJsonObject mccncObject;
    mccncObject.insert("mcc", mccnc.mcc);
    mccncObject.insert("mnc", mccnc.mnc);
    objectWifiPosition.insert("mccnc", mccncObject);

    // 3
    QJsonArray wifiDataArray;
    for(int i=0; i<wifiDataList.count(); i++)
    {
        WifiData wifiData = wifiDataList[i];
        QJsonObject wifiItem;
        wifiItem.insert("bssid", wifiData.bssid);
        wifiItem.insert("rssi", wifiData.rssi);
        wifiDataArray.append(wifiItem);
    }
    objectWifiPosition.insert("wifi", wifiDataArray);

    // 4
    QJsonArray lbsDataArray;
    for(int i=0; i<lbsDataList.count(); i++)
    {
        LBSData lbsData = lbsDataList[i];
        QJsonObject lbsItem;
        lbsItem.insert("lac", lbsData.lac);
        lbsItem.insert("mciss", lbsData.mciss);
        lbsItem.insert("cellid", lbsData.cellid);
        lbsDataArray.append(lbsItem);
    }
    objectWifiPosition.insert("lbs", lbsDataArray);

    return objectWifiPosition;
}

QDataStream &operator>>(QDataStream &in, WifiData &data)
{
    // 1475905BD30E25 前面 6byte 为 bssid，后面 1byte 为 rssi
    QByteArray bssid;
    for(int i=0; i<6; i++)
    {
        qint8 temp;
        in >> temp;
        bssid.append(temp);
    }

    data.bssid = bssid.toHex();

    QByteArray rssi;
    for(int i=0; i<1; i++)
    {
        qint8 temp;
        in >> temp;
        rssi.append(temp);
    }
    data.rssi = rssi.toHex();

    return in;
}

QDataStream &operator>>(QDataStream &in, LBSData &data)
{
    /*               lac 2byte ; cellid 2byte; mciss 1byte
     * 2866 0F21 32  lac 10342 ; cellid 3873 ; mciss 50
     */

    QByteArray lac;
    for(int i=0; i<2; i++)
    {
        qint8 temp;
        in >> temp;
        lac.append(temp);
    }
    data.lac = lac.toHex();

    QByteArray cellid;
    for(int i=0; i<2; i++)
    {
        qint8 temp;
        in >> temp;
        cellid.append(temp);
    }
    data.cellid = cellid.toHex();

    QByteArray mciss;
    for(int i=0; i<1; i++)
    {
        qint8 temp;
        in >> temp;
        mciss.append(temp);
    }
    data.mciss = mciss.toHex();

    return in;
}

QDataStream &operator>>(QDataStream &in, MCCMNC &data)
{
    /*
     * http://blog.chinaunix.net/uid-20484604-id-1941290.html
     * MCC: Mobile Country Code，移动国家码，MCC的资源由国际电联（ITU）统一分配和管理，唯一识别移动用户所属的国家，共3位，中国为460;
     * MNC: Mobile Network Code，移动网络码，共2位，中国移动TD系统使用00，中国联通GSM系统使用01，中国移动GSM系统使用02，中国电信CDMA系统使用03
    */

    // 01CC 00 为 460(mcc) 0(mnc)
    qint8 byte1,  byte2,  byte3;
    in >> byte1 >>byte2 >>byte3;

    QByteArray mccByteArray;
    mccByteArray.append(byte1);
    mccByteArray.append(byte2);
    QString mccString = mccByteArray.toHex();

    data.mcc = QString::number(mccString.toInt(0,16));
    data.mnc = QString::number(byte3);

    return in;
}

QDataStream &operator>>(QDataStream &in, BCDDateTime &data)
{
    // 16 04 13 03 18 49
    QByteArray dateTimeByteArray;
    for(int i=0; i<6; i++)
    {
        qint8 temp;
        in >> temp;
        dateTimeByteArray.append(temp);
    }
    QString dateTimeString = "20";
    dateTimeString += dateTimeByteArray.toHex();
    QDateTime dateTime = QDateTime::fromString(dateTimeString, "yyyyMMddhhmmss");

    if(dateTime.isValid())
        data.dateTime = dateTime.toString("yyyyMMddhhmmss");
    else
        data.dateTime = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");

    return in;
}
