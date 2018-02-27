#include "ShoeManagerNetwork.hpp"
#include <QJsonObject>

ShoeManagerNetwork::ShoeManagerNetwork()
{
    mConfig = ShoeManagerNetworkConfig::getInstance();
    pNetwork = ShoeManagerNetworkAccessManager::getInstance();
}

ShoeManagerNetwork *ShoeManagerNetwork::getInstance()
{
    static ShoeManagerNetwork oInstance;
    return &oInstance;
}

ShoeManagerNetworkResult *ShoeManagerNetwork::registerQRCode(QString telephone)
{
    QJsonObject oJsonData = {
        {"telephone", telephone},
    };

    return pNetwork->execJsonRequestSync(mConfig->getApi_registerQRcode(), "post", oJsonData);
}

ShoeManagerNetworkResult *ShoeManagerNetwork::registerAccount(QString telephone, QString passwd, QString QRCode, QString name)
{
    QJsonObject oJsonData = {
        {"telephone", telephone},
        {"password",  passwd},
        {"qrcode", QRCode},
        {"name", name}
    };

    return pNetwork->execJsonRequestSync(mConfig->getApi_register(), "post", oJsonData);
}

ShoeManagerNetworkResult *ShoeManagerNetwork::login(QString telephone, QString password)
{
    QJsonObject oJsonData = {
        {"telephone", telephone},
        {"password",  password}
    };

    return pNetwork->execJsonRequestSync(mConfig->getApi_login(), "post", oJsonData);
}

ShoeManagerNetworkResult *ShoeManagerNetwork::passwdQRCode(QString telephone)
{
    QJsonObject oJsonData = {
        {"telephone", telephone},
    };

    return pNetwork->execJsonRequestSync(mConfig->getApi_passwordQRcode(), "post", oJsonData);
}

ShoeManagerNetworkResult *ShoeManagerNetwork::passwdRetrive(QString telephone, QString passwd, QString QRCode)
{
    QJsonObject oJsonData = {
        {"telephone", telephone},
        {"newpassword", passwd},
        {"qrcode", QRCode}
    };

    return pNetwork->execJsonRequestSync(mConfig->getApi_passwordRetrive(), "post", oJsonData);
}

ShoeManagerNetworkResult *ShoeManagerNetwork::passwdUpdate(QString passwd)
{
    QJsonObject oJsonData = {
        {"new_password", passwd},
    };

    return pNetwork->execJsonRequestSync(mConfig->getApi_passwordUpdate(), "post", oJsonData);
}

ShoeManagerNetworkResult *ShoeManagerNetwork::userProfile()
{
    return pNetwork->execJsonRequestAsyn(mConfig->getApi_userProfile(), "post", QJsonObject());
}

ShoeManagerNetworkResult *ShoeManagerNetwork::userProfileUpdate(QString name)
{
    QJsonObject oJsonData = {
        {"new_name", name},
    };

    return pNetwork->execJsonRequestSync(mConfig->getApi_userProfileUpdate(), "post", oJsonData);
}

ShoeManagerNetworkResult *ShoeManagerNetwork::bindDevices()
{
    return pNetwork->execJsonRequestAsyn(mConfig->getApi_bindDevices(), "post", QJsonObject());
}

ShoeManagerNetworkResult *ShoeManagerNetwork::bindDevice(QString name, QString imei)
{
    QJsonObject oJsonData = {
        {"name", name},
        {"sid", imei}
    };

    return pNetwork->execJsonRequestSync(mConfig->getApi_bindDevice(), "post", oJsonData);
}

ShoeManagerNetworkResult *ShoeManagerNetwork::unbindDevice(QString imei)
{
    QJsonObject oJsonData = {
        {"sid", imei}
    };

    return pNetwork->execJsonRequestSync(mConfig->getApi_unbindDevice(), "post", oJsonData);
}

ShoeManagerNetworkResult *ShoeManagerNetwork::setDeviceIsOnline(QString imei, bool isOnline)
{
    QJsonObject oJsonData = {
        {"sid", imei},
        {"isOnline", online}
    };

    return pNetwork->execJsonRequestAsyn(mConfig->getApi_setDeviceIsOnline(), "post", oJsonData);
}

ShoeManagerNetworkResult *ShoeManagerNetwork::setDeviceIsSubscibed(QString imei, bool isSubscribed)
{
    QJsonObject oJsonData = {
        {"sid", imei},
        {"isSubscribed", isSubscribed}
    };

    return pNetwork->execJsonRequestAsyn(mConfig->getApi_setDeviceIsSubscribed(), "post", oJsonData);
}

ShoeManagerNetworkResult *ShoeManagerNetwork::setDevicePower(QString imei, int power)
{
    QJsonObject oJsonData = {
        {"sid", imei},
        {"power", power}
    };

    return pNetwork->execJsonRequestAsyn(mConfig->getApi_setDevicePower(), "post", oJsonData);
}

ShoeManagerNetworkResult *ShoeManagerNetwork::getDeviceStatus(QStringList imeis)
{
    QJsonObject oJsonData = {
        {"sids", imeis},
    };

    return pNetwork->execJsonRequestAsyn(mConfig->getApi_getDeviceStatus(), "post", oJsonData);
}

ShoeManagerNetworkResult *ShoeManagerNetwork::addDeviceGPS(QString imei, QJsonObject object)
{
    QJsonObject oJsonData = {
        {"sid", imei},
        {"gps", object}
    };

    return pNetwork->execJsonRequestAsyn(mConfig->getApi_addDeviceGPS(), "post", oJsonData);
}

ShoeManagerNetworkResult *ShoeManagerNetwork::addDeviceWifiLBS(QString imei, QJsonObject object)
{
    QJsonObject oJsonData = {
        {"sid", imei},
        {"wifilbs", object}
    };

    return pNetwork->execJsonRequestAsyn(mConfig->getApi_addDeviceWifiLBS(), "post", oJsonData);
}

ShoeManagerNetworkResult *ShoeManagerNetwork::getDevicePosition(QStringList imeis, int type)
{
    QJsonObject oJsonData = {
        {"sid", imeis},
        {"type", type}
    };

    return pNetwork->execJsonRequestAsyn(mConfig->getApi_getDevicePosition(), "post", oJsonData);
}
