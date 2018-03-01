#include "ShoeManagerNetworkConfig.hpp"

ShoeManagerNetworkConfig *ShoeManagerNetworkConfig::getInstance()
{
    static ShoeManagerNetworkConfig oInstance;
    return &oInstance;
}

ShoeManagerNetworkConfig::ShoeManagerNetworkConfig()
{
//#define LoaclServer
#ifdef LoaclServer
    mServer = "http://127.0.0.1:5555/api/v2.0/";
#else
    mServer = "http://www.shakeda.com:5555/api/v2.0/";
#endif

    mApi_login = "account/login";

    mApi_passwordQRcode = "account/password/qrcode";
    mApi_passwordRetrive = "account/password/retrieve";
    mAPi_registerQRcode = "account/register/qrcode";
    mApi_register = "account/register";

    mApi_userProfile = "account/profile";
    mApi_userProfileUpdate = "account/profile/update";
    mApi_passwordUpdate = "account/password/update";

    mApi_bindDevices = "account/devices";
    mApi_bindDevice = "account/devices/add";
    mApi_unbindDevice = "account/devices/remove";


    mApi_setDeviceIsOnline = "devicemanager/setisonline";
    mApi_setDeviceIsSubcribed = "devicemanager/setissubscribed";
    mApi_setDevicePower = "devicemanager/setpower";

    mApi_addDeviceGPS = "position/addgps";
    mApi_addDeviceWifiLBS = "position/addwifilbs";

    mApi_getDeviceStatus = "devicemanager/getstatus";
    mApi_getDevicePosition = "position/latest";
}

QString ShoeManagerNetworkConfig::getApi_passwordUpdate() const
{
    return mServer + mApi_passwordUpdate;
}

QString ShoeManagerNetworkConfig::getApi_setDeviceIsOnline()
{
    return mServer + mApi_setDeviceIsOnline;
}

QString ShoeManagerNetworkConfig::getApi_setDeviceIsSubscribed()
{
    return mServer + mApi_setDeviceIsSubcribed;
}

QString ShoeManagerNetworkConfig::getApi_setDevicePower()
{
    return mServer + mApi_setDevicePower;
}

QString ShoeManagerNetworkConfig::getApi_getDeviceStatus()
{
    return mServer + mApi_getDeviceStatus;
}

QString ShoeManagerNetworkConfig::getApi_addDeviceGPS()
{
    return mServer + mApi_addDeviceGPS;
}

QString ShoeManagerNetworkConfig::getApi_addDeviceWifiLBS()
{
    return mServer + mApi_addDeviceWifiLBS;
}

QString ShoeManagerNetworkConfig::getApi_getDevicePosition()
{
    return mServer + mApi_getDevicePosition;
}

QString ShoeManagerNetworkConfig::getApi_unbindDevice() const
{
    return mServer + mApi_unbindDevice;
}

QString ShoeManagerNetworkConfig::getApi_bindDevice() const
{
    return mServer + mApi_bindDevice;
}

QString ShoeManagerNetworkConfig::getApi_bindDevices() const
{
    return mServer + mApi_bindDevices;
}

QString ShoeManagerNetworkConfig::getApi_userProfileUpdate() const
{
    return mServer + mApi_userProfileUpdate;
}

QString ShoeManagerNetworkConfig::getApi_userProfile() const
{
    return mServer + mApi_userProfile;
}

void ShoeManagerNetworkConfig::setToken(const QString &token)
{
    mToken = token;
}

QString ShoeManagerNetworkConfig::getApi_login() const
{
    return mServer + mApi_login;
}

QString ShoeManagerNetworkConfig::getApi_passwordQRcode() const
{
    return mServer +  mApi_passwordQRcode;
}

QString ShoeManagerNetworkConfig::getApi_passwordRetrive() const
{
    return mServer +  mApi_passwordRetrive;
}

QString ShoeManagerNetworkConfig::getApi_registerQRcode() const
{
    return mServer +  mAPi_registerQRcode;
}

QString ShoeManagerNetworkConfig::getApi_register() const
{
    return mServer +  mApi_register;
}
