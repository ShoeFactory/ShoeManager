#ifndef SHOEMESSAGEGPS_H
#define SHOEMESSAGEGPS_H

#include <QByteArray>
#include <QDateTime>
#include <QJsonObject>

#include "shoemanagermodel_global.h"

/**
 * @brief GPS信息 26字节
 */
class SHOEMANAGERMODELSHARED_EXPORT ShoeMessageGPS
{
public:
    ShoeMessageGPS();
    ShoeMessageGPS(const ShoeMessageGPS &other);
    ShoeMessageGPS(const QByteArray byteArray);

    //  6字节 时间
    QDateTime getDateTime();

    //  1字节 信息长度与参与定位的卫星数 各站四位
    void getMessageLengthAndSatelliteCount(int &ML, int &SC);

    //  4字节 经度  x°y'       (x*60+y)*30000        = result  ==> 16进制
    double  getLongitudeDouble();
    QString getLongitudeString();
    quint32 getLongitude();

    //  4字节 维度  22°32.7658 (22*60+32.7658)*30000 = 4056974 ==> 16进制
    double getLatitudeDouble();
    QString getLatitudeString();
    quint32 getLatitude();

    //  1字节 速度 公里/小时
    int getSpeed();

    //  2字节 状态(东西经，南北纬，是否定位 前4位)、航向(332° 后10位)
    void getStatusAndDirection(QString &status, int&direction);

    //  8字节 保留位

    //  返回jsonObject
    QJsonObject getObject();

    //  原始数据
    void parseData(const QByteArray &data);

private:
    QByteArray m_data;
};

#endif // SHOEMESSAGEGPS_H
