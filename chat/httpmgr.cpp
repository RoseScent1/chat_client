#include "httpmgr.h"
#include "global.h"

HttpMgr::HttpMgr()
{
    connect(this, &HttpMgr::sig_http_finish, this, &HttpMgr::slot_http_finish);
}

void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod)
{
    QByteArray data = QJsonDocument(json).toJson();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(data.length()));
    auto self = shared_from_this();
    QNetworkReply * reply = _manger.post(request, data);
    QObject::connect(reply, &QNetworkReply::finished, [self,reply, req_id, mod]() {
        if (reply->error() != QNetworkReply::NetworkError::NoError) {
            // chu li cuo wo
            qDebug() << reply->errorString();
            // fasong xinhao tongzhi wancheng
            emit self->sig_http_finish(req_id, "", ErrorCodes::ERR_NETWORK, mod);
            reply->deleteLater();
            return;
        }
        // wu cuowu
        QString res = reply->readAll();
        emit self->sig_http_finish(req_id, res, ErrorCodes::SUCCESS, mod);
        reply->deleteLater();
        return ;
    });
}

void HttpMgr::slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod)
{
    if (mod == Modules::REGISTERMOD) {
        // fasong xinhao  tongzhi zhiding http de xiangying jieshu le
        emit sig_reg_mod_finish(id, res, err);
    }
}
HttpMgr::~HttpMgr()
{

}
