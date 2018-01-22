#ifndef SHOEMESSAGELOGIN_H
#define SHOEMESSAGELOGIN_H

#include <QByteArray>
#include "shoemanagermodel_global.h"

class SHOEMANAGERMODELSHARED_EXPORT ShoeMessageLogin
{
public:

    ShoeMessageLogin();
    ShoeMessageLogin(const ShoeMessageLogin &other);

    // 留作以后的标识
    QString getIMEI();

    // 返回核心
    QByteArray getData() const;
    void setData(QByteArray data);

    void setIMEI(QByteArray imei);
    void setVersion(QByteArray version);

private:
    QByteArray m_imei;
    QByteArray m_version;
};
#endif // SHOEMESSAGELOGIN_H
