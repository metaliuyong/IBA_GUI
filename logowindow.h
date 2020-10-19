#ifndef LOGOWINDOW_H
#define LOGOWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QPainter>

class LogoWindow : public QMainWindow
{
public:
    LogoWindow(QWidget *parent = nullptr);
    ~LogoWindow();
    void paintEvent(QPaintEvent *event);

private:

};



#endif // LOGOWINDOW_H
