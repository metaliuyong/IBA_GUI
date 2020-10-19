#include "mainwindow.h"
#include "logowindow.h"
#include <QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogoWindow logo;
    logo.show();

    QTime dieTime= QTime::currentTime().addSecs(2);
    while (QTime::currentTime() < dieTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    logo.close();
    MainWindow w;
    w.show();

    return a.exec();
}

