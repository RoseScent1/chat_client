#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <iostream>
#include "global.h"
#include "httpmgr.h"
RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->pass_edit->setEchoMode(QLineEdit::Password);
    ui->err_tip->setProperty("state", "normal");
    repolish(ui->err_tip);
    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish, this, &RegisterDialog::slot_reg_mod_finish);
    initHttpHandlers();
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
    std::cout << "Register deleted" << std::endl;
}

void RegisterDialog::on_ver_butten_clicked()
{
    auto email = ui->email_edit->text();
    static QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch();
    if (match) {
        QJsonObject json_obj;
        json_obj["email"] = email;
        HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix + "/get_varifycode"), json_obj, ReqId::Id_GET_VARIFY_CODE, Modules::REGISTERMOD);
    } else {
        showTip(tr("邮箱错误"), false);
    }
}

void RegisterDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if (err != ErrorCodes::SUCCESS) {
        showTip(tr("网络错误"), false);
        return ;
    }
    // decode json
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    if (jsonDoc.isNull()) {
        showTip(tr("json解析失败"), false);
        return ;
    }
    if (!jsonDoc.isObject()) {
        showTip(tr("json解析失败"), false);
        return ;
    }


    _handlers[id](jsonDoc.object());
    return ;

}

void RegisterDialog::initHttpHandlers()
{
    _handlers.insert(ReqId::Id_GET_VARIFY_CODE, [this](const QJsonObject &jsonObj){
        int error = jsonObj["error"].toInt();
        if (error != ErrorCodes::SUCCESS) {
            showTip(tr("注册失败"), false);
            return ;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("注册成功"), true);
        qDebug() << "emalil is" << email;
    });
}

void RegisterDialog::showTip(QString str, bool b_ok)
{
    if (b_ok)
        ui->err_tip->setProperty("state", "err");
    else
        ui->err_tip->setProperty("state", "normal");
    ui->err_tip->setText(str);
    repolish(ui->err_tip);
}

