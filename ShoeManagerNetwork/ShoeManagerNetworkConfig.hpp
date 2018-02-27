#ifndef SHOEMANAGERNETWORKCONFIG_HPP
#define SHOEMANAGERNETWORKCONFIG_HPP

#include <QObject>
#include "shoemanagernetwork_global.h"

class SHOEMANAGERNETWORKSHARED_EXPORT ShoeManagerNetworkConfig
{
public:
    static ShoeManagerNetworkConfig* getInstance();

    QString getToken() { return mToken; }
    void setToken(const QString &token);

    QString getApi_login() const;
    QString getApi_passwordQRcode() const;
    QString getApi_passwordRetrive() const;
    QString getApi_registerQRcode() const;
    QString getApi_register() const;

    QString getApi_userProfile() const;
    QString getApi_userProfileUpdate() const;

    QString getApi_bindDevices() const;
    QString getApi_bindDevice() const;
    QString getApi_unbindDevice() const;

    QString getApi_passwordUpdate() const;

    QString getApi_setDeviceIsOnline();
    QString getApi_setDeviceIsSubscribed();
    QString getApi_setDevicePower();

    QString getApi_getDeviceStatus();
    QString getApi_addDeviceGPS();
    QString getApi_addDeviceWifiLBS();
    QString getApi_getDevicePosition();

private:
    ShoeManagerNetworkConfig();

private:
    QString mToken;
    QString mServer;

    QString mApi_login;
    QString mApi_passwordQRcode;
    QString mApi_passwordRetrive;
    QString mAPi_registerQRcode;
    QString mApi_register;

    QString mApi_userProfile;
    QString mApi_userProfileUpdate;
    QString mApi_passwordUpdate;

    QString mApi_bindDevice;
    QString mApi_unbindDevice;

    QString mApi_setDeviceIsOnline;
    QString mApi_setDeviceIsSubcribed;
    QString mApi_setDevicePower;

    QString mApi_addDeviceGPS;
    QString mApi_addDeviceWifiLBS;

    QString mApi_bindDevices;
    QString mApi_getDeviceStatus;
    QString mApi_getDevicePosition;
};

#endif // SHOEMANAGERNETWORKCONFIG_HPP
