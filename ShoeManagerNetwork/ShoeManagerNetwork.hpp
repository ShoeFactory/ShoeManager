#ifndef SHOEMANAGERNETWORKKIT_HPP
#define SHOEMANAGERNETWORKKIT_HPP

#include <QObject>
#include <QNetworkReply>

#include "shoemanagernetwork_global.h"
#include "ShoeManagerNetworkConfig.hpp"
#include "ShoeManagerNetworkAccessManager.hpp"
#include "ShoeManagerNetworkResult.hpp"

class SHOEMANAGERNETWORKSHARED_EXPORT ShoeManagerNetwork : public QObject
{
public:
    static ShoeManagerNetwork *getInstance();

    //! 发送注册验证码
    ShoeManagerNetworkResult *registerQRCode(QString telephone);

    //! 注册账号
    ShoeManagerNetworkResult *registerAccount(QString telephone, QString passwd, QString QRCode, QString name);

    //! 同步登陆
    ShoeManagerNetworkResult *login(QString telephone, QString password);

    //! 发送改密验证码
    ShoeManagerNetworkResult *passwdQRCode(QString telephone);

    //! 找回密码
    ShoeManagerNetworkResult *passwdRetrive(QString telephone, QString passwd, QString QRCode);

    //! 更新密码
    ShoeManagerNetworkResult *passwdUpdate(QString passwd);

    //! 获取用户账号资料
    ShoeManagerNetworkResult *userProfile();

    //! 修改用户账户资料
    ShoeManagerNetworkResult *userProfileUpdate(QString name);

    //! 获取关联设备列表
    ShoeManagerNetworkResult *bindDevices();

    //! 关联设备
    ShoeManagerNetworkResult *bindDevice(QString name, QString imei);

    //! 取关设备
    ShoeManagerNetworkResult *unbindDevice(QString imei);

    //! 设备在线
    ShoeManagerNetworkResult *deviceOnline(QString imei);

    //! 设备下线
    ShoeManagerNetworkResult *deviceOffline(QString imei);

    //! 设备是否在线
    ShoeManagerNetworkResult *isDeviceOnline(QString imei);

    //! 设置设备状态
    ShoeManagerNetworkResult *setDeviceStatus(QString imei, QJsonObject object);

    //! 获取设备状态
    ShoeManagerNetworkResult *getDeviceStatus(QString imei);

    //! 添加GPS
    ShoeManagerNetworkResult *addDeviceGPS(QString imei, QJsonObject object);

    //! 添加wifilbs
    ShoeManagerNetworkResult *addDeviceWifiLBS(QString imei, QJsonObject object);

    //! 获取定位
    ShoeManagerNetworkResult *getDevicePosition(QString imei);

private:
    ShoeManagerNetwork();

private:
    ShoeManagerNetworkConfig *mConfig;
    ShoeManagerNetworkAccessManager *pNetwork;
};

#endif // SHOEMANAGERNETWORKKIT_HPP
