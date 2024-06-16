#ifndef GLOBAL_H
#define GLOBAL_H
#include <QWidget>
#include <functional>
#include "QStyle"
#include <QRegularExpression>
#include <memory>
#include <iostream>
#include <mutex>
#include <QByteArray>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QDir>
extern std::function<void(QWidget *)> repolish;
enum ReqId {
    Id_GET_VARIFY_CODE = 1001, //get varify code
    ID_REG_USER = 1002, // register user
};

enum Modules {
    REGISTERMOD = 0,
};

enum ErrorCodes {
    SUCCESS = 0,
    ERR_JSON = 1, // json decode err
    ERR_NETWORK = 2, //net err
};

extern QString gate_url_prefix;
#endif // GLOBAL_H
