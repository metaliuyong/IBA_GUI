#include "file.h"
#include <QDebug>
#include <QDirIterator>

namespace fs = std::filesystem;

File::File(): path(""), dataVec({}){
    dataVec.reserve(2048);//通过reserve来避免realloc造成的开销
}

File::File(QString p): path(p), dataVec({}){
    dataVec.reserve(2048);
}

File::~File(){

}


//打开一个目录获取其中所有的Spe文件对其进行trans_spe_to_txt操作
bool File::trans_spe_to_txt_batch(QString dir){
   QDirIterator it(dir, QDirIterator::Subdirectories);
   while(it.hasNext()){
       QString fi = it.next();
       if(fi.split(".").at(1) == "Spe"){
           trans_spe_to_txt(fi);
       }
   }
   return true;
}


//打开一个文件读取道数信息并且将其转换为txt文件.
bool File::trans_spe_to_txt(QString f){
    QFile rf(f);
    if(!rf.open(QIODevice::ReadOnly)){
        return false;
    }
    QString w = f.split(".").at(0) + ".txt";
    QFile wf(w);
    if(!wf.open(QIODevice::WriteOnly)){
        return false;
    }
    QTextStream out(&wf);

    //过滤掉11条嘈杂信息
    for(int i = 0; i < 11; ++i){
        rf.readLine();
    }
    QString line = rf.readLine();

    //从第12行中获取道数
    QStringList list = line.split(" ");
    int cEnd = list[1].toInt();

    //不能读到end,因为最后也有无用信息
    for(int i = 1; i <= cEnd + 1; ++ i){
        line = rf.readLine();
        int c = line.toInt();

        //将数据读到File实例中并且写到磁盘文件txt中.
        Data d(i, c);
        this->dataVec.push_back(d);
        out << i << "\t" << c << "\n";
    }
    rf.close();
    wf.close();
    return true;
}

bool File::plotSpectrum(QString f, QChart *chart){
    this->dataVec.clear();//因为重新从文件中读取数据了，所以开始时要清零
    QFile rf(f);
    if(!rf.open(QIODevice::ReadOnly)){
        return false;
    }
    QString line;
    int ch = 0;
    int co = 0;
    Data d {};

    QLineSeries *series0 = new QLineSeries();
    series0->setName("能谱曲线");
    chart->addSeries(series0);

    int maxCount = 0;

    while(!rf.atEnd()){
        line = rf.readLine();
        QStringList spl {};
        if(line.contains("\t")){
            spl = line.split("\t");
        }
        else{
            //simplified可以去掉QString首位的空格，并将QString中间的多个空格变为一个.
            spl = line.simplified().split(" ");
        }
        ch = spl[0].toInt();
        co = spl[1].toInt();

        if(co > maxCount){
            maxCount = co;
        }
        series0->append(ch, co);

        //qDebug() << ch << co;
        d.setChannel(ch);
        d.setCount(co);
        this->dataVec.push_back(d);
    }
    rf.close();
    QValueAxis *axisX = new QValueAxis();
    QValueAxis *axisY = new QValueAxis();

    axisX->setRange(0, ch);
    axisX->setTitleText("time/sec");

    axisY->setRange(0, maxCount);
    axisY->setTitleText("value");

    chart->setAxisX(axisX, series0);
    chart->setAxisY(axisY, series0);
    return true;
}
