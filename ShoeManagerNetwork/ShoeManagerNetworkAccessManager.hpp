#ifndef SHOEMANAGERNETWORKMANAGER_HPP
#define SHOEMANAGERNETWORKMANAGER_HPP

#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include "ShoeManagerNetworkResult.hpp"

class ShoeManagerNetworkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT

public:
    static ShoeManagerNetworkAccessManager *getInstance();

    // 同步请求
    ShoeManagerNetworkResult * execJsonRequestSync(const QString &url,
                                 const QString &method,
                                 const QJsonObject &reqBody);
    // 异步请求
    ShoeManagerNetworkResult * execJsonRequestAsyn(const QString &url,
                                 const QString &method,
                                 const QJsonObject &reqBody);

private:
    ShoeManagerNetworkAccessManager();
    QNetworkReply *execRequest(const QString &url,
                               const QString &method,
                               const QJsonObject &reqBody);
};

#endif // SHOEMANAGERNETWORKMANAGER_HPP
