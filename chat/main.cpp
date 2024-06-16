#include "mainwindow.h"
#include <QFile>
#include <QApplication>
#include <QSettings>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss(":/stylesheet.qss");

    // 读qss
    if (qss.open(QFile::ReadOnly)) {
        qDebug("open success");
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();

    } else {
        qDebug("open failed");
    }

    // 读配置
    QString file_name = "config.ini";
    QString app_path = QCoreApplication::applicationDirPath();
    QString config_path = QDir::toNativeSeparators(app_path + QDir::separator() +file_name);
    QSettings settings(config_path,QSettings::IniFormat);
    QString gate_host = settings.value("GateServer/host").toString();
    QString gate_port = settings.value("GateServer/port").toString();
    gate_url_prefix = "http://" + gate_host+":"+gate_port;
    std::cout << gate_url_prefix.toStdString() << std::endl;
    MainWindow w;
    w.show();
    return a.exec();
}
