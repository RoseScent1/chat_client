#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registerdialog.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    login_di = new LoginDialog(this);
    setCentralWidget(login_di);
    login_di->show();

    // create register connection
    connect(login_di, &LoginDialog::switchRegister, this, &MainWindow::SlotSwitchReg);
    register_di = new RegisterDialog(this);

    login_di->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

    register_di->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    register_di->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SlotSwitchReg()
{
    setCentralWidget(register_di);
    login_di->hide();
    register_di->show();
}

