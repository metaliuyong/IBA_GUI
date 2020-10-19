#include "logowindow.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QTimer>


LogoWindow::LogoWindow(QWidget *parent):
    QMainWindow(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    int screen_width = QApplication::desktop()->width();
    int screen_height = QApplication::desktop()->height();
    this->resize(screen_width/2, screen_height/2);
    this->move(screen_width/2 - this->width()/2, screen_height/2-this->height()/2);
}

LogoWindow::~LogoWindow()
{
}

void LogoWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPixmap pixmap("back1.jpg");
    painter.drawPixmap(this->rect(), pixmap);
}



