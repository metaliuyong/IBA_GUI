#include "mainwindow.h"
#include "file.h"
#include <QDir>
#include <QChartView>
#include <QChart>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    //设置主窗口标题
    this->setWindowTitle("综合离子束分析软件");

    //设置程序图标
    //this->setWindowIcon(QIcon("/Users/liuyong/Desktop/app.icns"));

    //根据不同屏幕分辨率调节主窗口的大小始终为屏幕大小的4/5,并且总是居中.
    //TODO:需要考虑存在多块屏幕时的情况.
    int screen_width = QApplication::desktop()->width();
    int screen_height = QApplication::desktop()->height();
    this->resize(screen_width*4/5, screen_height*4/5);
    this->move(screen_width/2 - this->width()/2, screen_height/2-this->height()/2);



    //设置菜单栏，包含[File | Edit | Plot | Tools | Help]
    QMenuBar *menubar = menuBar();
    QMenu *pFile = menubar->addMenu("File");
    QMenu *pEdit = menubar->addMenu("Edit");
    QMenu *pPlot = menubar->addMenu("Plot");
    QMenu *pTools = menubar->addMenu("Tools");
    QMenu* pHelp = menubar->addMenu("Help");

    //菜单栏File的Action,包含[New | Open]
    QAction *pNew = pFile->addAction("New");
    QAction *pOpen = pFile->addAction("Open");
//    connect(pOpen, &QAction::triggered,
//           [=]()
//           {
//               QString open_path = QFileDialog::getOpenFileName(this, "open", "../",
//                          "Text(*.txt)");
//               if(!open_path.isEmpty())
//               {
//                   //File::read_channel_data(open_path, spectrum_data);
//               }
//               for(std::vector<Data>::iterator iter = spectrum_data.begin(); iter != spectrum_data.end(); iter ++)
//               {
//                   qDebug() << iter->channel << " " << iter->experimental << " " << iter->simulated;
//               }
//           }
//           );


    pFile->addSeparator();

    //菜单栏Edit的Action
    QAction* pExportData = pEdit->addAction("Export data");
    QAction* pExportImag = pEdit->addAction("Export picture");


    //菜单栏Plot的Action
    QAction* pPlotSpectrum = pPlot->addAction("Plot Spectrum");
    connect(pPlotSpectrum, &QAction::triggered,
            [=]()
            {
                QString fi = QFileDialog::getOpenFileName(this, "open", "../", "Text(*.txt)");
                if(!fi.isEmpty()){
                    qDebug() << fi;
                    File f(fi);

                    //清理掉之前的曲线和坐标轴，否则会出现多张图片重叠的现象
                    chart->removeAllSeries();
                    for(auto x : chart->axes()){
                        chart->removeAxis(x);
                    }
                    f.plotSpectrum(fi, this->chart);
                }
            }
    );

    //菜单栏Tools的Action，包括[Convert Spe | Convert Spe Dir]

    //Convert Spe打开一个Spe文件，将其转换为txt格式
    QAction *pConvertSpe = pTools->addAction("Convert Spe");
    connect(pConvertSpe, &QAction::triggered,
           [=](){
               QString filter = "Spe文件(*.Spe)";
               QString open_dir = QFileDialog::getOpenFileName(this, "Convert Spe to Txt", "../", filter);
               if(!open_dir.isEmpty()){
                   //qDebug() << open_dir;
                   File f(open_dir);
                   if(f.trans_spe_to_txt(open_dir)){
                       label->setText("The File has been transfer to txt");
                   }
               }
           }
           );


    //Convert Spe Dir打开一个文件夹，将其下的Spe文件转换为txt格式.
    QAction *pConvertSpeDir = pTools->addAction("Convert Spe Dir");
    connect(pConvertSpeDir, &QAction::triggered,
           [=](){
               QString open_dir = QFileDialog::getExistingDirectory(this, "open", "../", QFileDialog::ShowDirsOnly);
               if(!open_dir.isEmpty()){
                   //qDebug() << open_dir;
                   File f(open_dir);
                   if(f.trans_spe_to_txt_batch(open_dir)){
                        label->setText("The File in Directory has been transfer to txt");
                   }
               }
           }
           );

    //菜单栏Help的Actions

    //打开User Manual
    QAction* pManual = pHelp->addAction("User Manual");
    connect(pManual, &QAction::triggered,
           [=]()
           {
                bool answer = QMessageBox::question(this, "Question", "Do you want to open manual.pdf?");
                //这里应该用一种通用的路径表示方式，在全平台通用，并且文件在安装目录下
                QString manual_path = "/Users/liuyong/Desktop/IBA_CUI2/Manual.pdf";
                if(answer){
                    bool is_open = QDesktopServices::openUrl(QUrl::fromLocalFile(manual_path));
                    if(!is_open){
                        qDebug() << "Could not open manual! Please check it.";
                    }
                }
           }
            );

    //薛老师主页
    QAction* pHomePage = pHelp->addAction("Home Page");
    connect(pHomePage, &QAction::triggered,
            []()
            {
                QString homepage_url = "http://faculty.pku.edu.cn/~ymQJbu/zh_CN/index.htm";
                bool is_open = QDesktopServices::openUrl(QUrl(homepage_url));
                if(!is_open){
                    qDebug() << "Could not open Homepage! Please check it.";
                }
            }
            );


    //软件相关信息
    QAction* pInformation = pHelp->addAction("Information");
    connect(pInformation, &QAction::triggered,
            [=]()
            {
                QMessageBox::about(this, "About IBA_CUI", "IBA_GUI v0.0\n\nOrg: Peking\
 University\nAuthor: Liu Yong\nEmail: metaliuyong@gmail.com\n");
            }
            );

    //开发工具Qt的信息
    QAction* pDevelopTool = pHelp->addAction("Develop Tool");
    connect(pDevelopTool, &QAction::triggered,
            [=]()
            {
                QMessageBox::aboutQt(this, "About Qt");
            }
            );



    //工具栏
    QToolBar *toolbar = addToolBar("toolbar");
    toolbar->addAction(pOpen);


    //状态栏
    label->setText("IBA解谱程序");
    statusbar->addWidget(label);
    statusbar->addWidget(new QLabel("UTF-8", this));
    statusbar->addPermanentWidget(new QLabel("MacOs 10.16"));

    //核心控件，文本编辑区
//    QTextEdit* textedit = new QTextEdit(this);
//    setCentralWidget(textedit);
//    setMenuBar(menubar);

    //画图区，ChartView
    this->setCentralWidget(chartView);

    chartView->setChart(chart);

    chart->setTitle("能谱图");


}

MainWindow::~MainWindow()
{
}

void MainWindow::open_homepage()
{
    qDebug() << "url";
    QString homepage_url = "http://www.baidu.com";
    bool open_o = QDesktopServices::openUrl(QUrl(homepage_url));
    qDebug() << open_o;
}

