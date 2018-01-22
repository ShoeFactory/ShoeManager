#include "ShoeManagerNetworkResult.hpp"

void ShoeManagerNetworkResult::parseReply(QNetworkReply *pReply)
{
    if(pReply->error() == QNetworkReply::NoError)
    {
        QJsonParseError parseError;
        QJsonDocument oDoc = QJsonDocument::fromJson(pReply->readAll(), &parseError);

        // 一切正确
        if(parseError.error == QJsonParseError::NoError)
        {
            QJsonObject object = oDoc.object();
            this->oReturnCode = object["code"].toInt(ShoeManagerNetworkResult::Error_NoCode);
            this->oReturnMessage = object["message"].toString();
            this->oReturnData = object["data"];
        }

        // 解析错误
        else
        {
            this->oReturnCode = ShoeManagerNetworkResult::Error_ResponseFormat;
            this->oReturnMessage = QString("后台数据解析错误") + QString::number(parseError.error);
            // this->oReturnMessage = QString::number(parseError.error) + parseError.errorString();
        }
    }
    // 网络错误
    else
    {
        this->oReturnCode = ShoeManagerNetworkResult::Error_Network;
        this->oReturnMessage = QString("网络错误") + QString::number(pReply->error());
        // this->oReturnMessage = QString::number(pReply->error()) + pReply->errorString();
    }
}
