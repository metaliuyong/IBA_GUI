#ifndef FILE_H
#define FILE_H

#include <QVector>
#include "data.h"
#include <QFile>
#include <QString>
#include <QChart>
#include <QtCharts>

class File
{
public:
    QString path;
    QVector<Data> dataVec;

    File();
    File(QString p);
    ~File();

    //将spe文件转换为txt文件，转换成功后返回真bool值，给予状态栏反馈。
    bool trans_spe_to_txt_batch(QString dir);
    bool trans_spe_to_txt(QString f);

    //传入文件和需要显示画图的设备，画图成功后返回true，给予状态栏反馈。
    bool plotSpectrum(QString f, QChart *chart);
};

#endif // FILE_H
