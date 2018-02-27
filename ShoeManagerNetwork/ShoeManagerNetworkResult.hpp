#ifndef SHOEMANAGERNETWORKRESULT_HPP
#define SHOEMANAGERNETWORKRESULT_HPP

#include "shoemanagernetwork_global.h"

#include <QString>
#include <QJsonObject>
#include <QNetworkReply>
#include <QJsonParseError>

class SHOEMANAGERNETWORKSHARED_EXPORT ShoeManagerNetworkResult : public QObject
{
    Q_OBJECT
public:
    enum NetworkError{
        Error_Network = -100,
        Error_ResponseFormat = -300,
        Error_NoCode = -1,
        Error_NoError = 0,
    };

signals:
    void requestFinished();

public:
    void parseReply(QNetworkReply *pReply);

    int oReturnCode;
    QString oReturnMessage;
    QJsonObject oRequestData;
    QJsonValue oReturnData;
};

#endif // SHOEMANAGERNETWORKRESULT_HPP
