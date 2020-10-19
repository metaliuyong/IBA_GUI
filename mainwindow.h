#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QApplication>
#include <QDebug>
#include <QStatusBar>
#include <QLabel>
#include <QTextEdit> //核心控件，文本编辑区
#include <QDockWidget> //浮动窗口
#include <QMessageBox>
#include <QFileDialog>
#include <QMenu>
#include <QAction>
#include <QDialog>
#include <QMenuBar>
#include <QToolBar>
#include <QDesktopServices>
#include <QUrl>
#include <QFile>
#include <QtCharts>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QChartView *chartView = new QChartView(this);
    QChart *chart = new QChart();

    QStatusBar* statusbar = statusBar();
    QLabel* label = new QLabel(this);

    MainWindow(QWidget *parent = nullptr);
    void open_homepage();
    ~MainWindow();
};


#endif // MAINWINDOW_H
