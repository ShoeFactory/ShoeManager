#include <QString>
#include "ShoeMessageLogin.h"

ShoeMessageLogin::ShoeMessageLogin()
{

}

ShoeMessageLogin::ShoeMessageLogin(const ShoeMessageLogin &other)
{
    m_imei = other.m_imei;
    m_version = other.m_version;
}

QString ShoeMessageLogin::getIMEI()
{
    /**
      * 这里牵扯这个imei是bcd编码
      * 0123456789012345 m_imei.toHex() 是
      *  123456789012345 第一个去掉
      *
     */
    QString result = QString(m_imei.toHex());
    return  result.remove(0, 1);
}

QByteArray ShoeMessageLogin::getData() const
{
    QByteArray result;

    result.append(m_imei);
    result.append(m_version);

    return result;
}

void ShoeMessageLogin::setData(QByteArray data)
{
    m_imei.clear();
    m_imei = data.left(8);

    m_version.clear();
    m_version=data.right(1);
}

void ShoeMessageLogin::setIMEI(QByteArray imei)
{
    m_imei = imei;
}

void ShoeMessageLogin::setVersion(QByteArray version)
{
    m_version = version;
}
