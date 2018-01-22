#include <QString>
#include "ShoeMessageLogin.h"

QString ShoeMessageLogin::getIMEI()
{
    /**
      * 这里牵扯这个imei是bcd编码
      * 0123456789012345 m_imei.toHex() 是
      *  123456789012345 第一个去掉
      *
     */
    return mIMEI;
}

void ShoeMessageLogin::parseData(QByteArray data)
{
    // 登录包是个异常包
    // 0d 01 0356314041406741 35
    auto imeiBytes = data.mid(2, 8);
    auto versionBytes = data.right(1);

    mIMEI = imeiBytes.toHex();
    mIMEI = mIMEI.remove(0, 1);

    mVersion = versionBytes.toHex();
}
