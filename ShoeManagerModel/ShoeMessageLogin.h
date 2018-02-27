#ifndef SHOEMESSAGELOGIN_H
#define SHOEMESSAGELOGIN_H

#include <QByteArray>
#include "shoemanagermodel_global.h"

class SHOEMANAGERMODELSHARED_EXPORT ShoeMessageLogin
{
public:
    // 留作以后的标识
    QString getIMEI();
    void parseData(QByteArray data);

private:
    QString mIMEI;
    QString mVersion;
};
#endif // SHOEMESSAGELOGIN_H
