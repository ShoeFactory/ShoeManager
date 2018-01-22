#include "ShoeManagerNetworkAccessManager.hpp"
#include "ShoeManagerNetworkConfig.hpp"
#include <QEventLoop>

ShoeManagerNetworkAccessManager::ShoeManagerNetworkAccessManager()
{

}

QNetworkReply *ShoeManagerNetworkAccessManager::execRequest(const QString &url, const QString &method, const QJsonObject &reqBody)
{
    QNetworkRequest oRequest;
    oRequest.setUrl(QUrl(url));
    oRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QString token = QString("Token ") + ShoeManagerNetworkConfig::getInstance()->getToken();
    oRequest.setRawHeader(QByteArray("Authorization"), token.toUtf8());

    QList<QString>  methodList = {"POST", "GET"};
    int methodType = methodList.indexOf(method.toUpper());
    Q_ASSERT(methodType != -1);

    QNetworkReply *pReply;
    switch (methodType){
    case 0:
    {
        QJsonDocument doc(reqBody);
        pReply = QNetworkAccessManager::post(oRequest,doc.toJson());
    }
        break;
    case 1:
    {
        pReply = QNetworkAccessManager::get(oRequest);
    }
        break;
    default:
        break;
    }

    return pReply;
}

ShoeManagerNetworkAccessManager *ShoeManagerNetworkAccessManager::getInstance()
{
    static ShoeManagerNetworkAccessManager oInstance;
    return &oInstance;
}

ShoeManagerNetworkResult *ShoeManagerNetworkAccessManager::execJsonRequestSync(const QString &url, const QString &method, const QJsonObject &reqBody)
{
    auto *pReply = execRequest(url, method, reqBody);

    QEventLoop oLoop;
    connect(pReply,SIGNAL(finished()),&oLoop,SLOT(quit()));
    oLoop.exec();

    ShoeManagerNetworkResult *result = new ShoeManagerNetworkResult;

    // 记录请求
    QJsonObject adjustedReqBody = reqBody;
    adjustedReqBody.insert("requestUrl", QJsonValue(url));
    adjustedReqBody.insert("requestMethod", QJsonValue(method));
    result->oRequestData = adjustedReqBody;

    // 解析回复
    result->parseReply(pReply);

    return result;
}

ShoeManagerNetworkResult *ShoeManagerNetworkAccessManager::execJsonRequestAsyn(const QString &url, const QString &method, const QJsonObject &reqBody)
{
    auto *pReply = execRequest(url, method, reqBody);

    ShoeManagerNetworkResult *result = new ShoeManagerNetworkResult;

    // 记录请求
    QJsonObject adjustedReqBody = reqBody;
    adjustedReqBody.insert("requestUrl", QJsonValue(url));
    adjustedReqBody.insert("requestMethod", QJsonValue(method));
    result->oRequestData = adjustedReqBody;

    // 解析回复
    connect(pReply, &QNetworkReply::finished, [=]{
        result->parseReply(pReply);
        emit result->requestFinished();
    });

    return result;
}
