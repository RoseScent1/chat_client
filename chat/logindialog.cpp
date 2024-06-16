#include "logindialog.h"
#include "ui_logindialog.h"
#include <iostream>
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    connect(ui->reg_button, &QPushButton::clicked, this, &LoginDialog::switchRegister);
    ui->pass_edit->setEchoMode(QLineEdit::Password);
}

LoginDialog::~LoginDialog()
{
    delete ui;
    std::cout << "Login deleted" << std::endl;
}
