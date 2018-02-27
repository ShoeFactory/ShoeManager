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

    //=========================================
    //                  动作
    //=========================================

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

    //! 修改用户账户资料
    ShoeManagerNetworkResult *userProfileUpdate(QString name);

    //! 关联设备
    ShoeManagerNetworkResult *bindDevice(QString name, QString imei);

    //! 取关设备
    ShoeManagerNetworkResult *unbindDevice(QString imei);

    //! 设备在线状态
    ShoeManagerNetworkResult *setDeviceIsOnline(QString imei, bool isOnline);

    //! 设置设备电量
    ShoeManagerNetworkResult *setDevicePower(QString imei, int power);

    //! 设置设备订阅
    ShoeManagerNetworkResult *setDeviceIsSubscibed(QString imei, bool isSubscribed);

    //! 添加GPS
    ShoeManagerNetworkResult *addDeviceGPS(QString imei, QJsonObject object);

    //! 添加wifilbs
    ShoeManagerNetworkResult *addDeviceWifiLBS(QString imei, QJsonObject object);

    //=========================================
    //                  查询
    //=========================================

    //! 获取用户账号资料
    ShoeManagerNetworkResult *userProfile();

    //! 获取关联设备列表
    ShoeManagerNetworkResult *bindDevices();

    //! 获取设备状态  （电量 是否订阅 是否）
    ShoeManagerNetworkResult *getDeviceStatus(QStringList imeis);

    //! 获取定位
    ShoeManagerNetworkResult *getDevicePosition(QStringList imeis, int type);

private:
    ShoeManagerNetwork();

private:
    ShoeManagerNetworkConfig *mConfig;
    ShoeManagerNetworkAccessManager *pNetwork;
};

#endif // SHOEMANAGERNETWORKKIT_HPP
