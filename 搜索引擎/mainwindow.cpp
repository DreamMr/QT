#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<vector>
#include<fstream>
#include<string>
#include"QDebug"
#include<QUrl>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setTabsClosable(true);
    this->setVisible(false);
    this->setWindowTitle(this->windowTitle()+"-initializing......");
    progress=new QProgressDialog(this);
    ui->pushButton->setEnabled(false);
    progress->setValue(100);
    progress->setWindowTitle("initializing... please wait a moment");
    search=new Search_engine;
    thread.search=search;//将搜索引擎对象的地址给初始化线程中的search，使search的初始化在线程中进行，不影响界面
     connect(thread.search,SIGNAL(sendProgress(int)),progress,SLOT(setValue(int)));//将进度条与线程中的search进行绑定，方便传递进度
     connect(&thread,SIGNAL(finished()),this,SLOT(setCanVisiable()));//将线程的完成信号和setCanVisiable（）函数绑定
    progress->show();
    thread.start();//开始建立索引，初始化
     setWindowIcon(QIcon("tubiao.ico"));
}
/***************************
 * 当初始化完成时进度条销毁，并新建top 10 页面
 **************************/
void MainWindow::setCanVisiable()
{
    this->setVisible(true);
    ui->pushButton->setEnabled(true);
    this->setWindowTitle("fire");
    delete progress;
    //*********top 10**********
    page=new Page;
    for(int i=0;i<search->top.size();i++){//将可信度排名前十的网页放入page的vector中
        page->v.push_back(search->top[i]);
        //qDebug()<<QString::fromStdString(search->top[i].url.url);
    }
   connect(page,SIGNAL(sendpageurl(QString)),this,SLOT(receviveurl(QString)));//将page中发射的url信号传送到当前窗口，由当前窗口打开网页
   page->setPage(search->top.size());
   ui->tabWidget->addTab(page,"top 10");
    //************************
}

MainWindow::~MainWindow()
{
    delete ui;
}
//*******************
//将指定的页面关闭
//*******************
void MainWindow::on_tabWidget_tabCloseRequested(int index)
{

    ui->tabWidget->removeTab(index);
}
//*************根据传递的url打开网页*******
void MainWindow::receviveurl(QString url)
{
    search_page=new SEARCH_PAGE;
    QUrl qurl;
    qurl.setUrl(url);
    search_page->view->load(qurl);
    int tab=ui->tabWidget->addTab(search_page,url);
    ui->tabWidget->setCurrentIndex(tab);
}
//**********搜索按钮**********
void MainWindow::on_pushButton_clicked()
{
     page=new Page;
    int page_number=search->Search(ui->textEdit->toPlainText().toStdString(),10,page->v);//将关键词和page的网页数组通过引用的方式传给search，返回要显示的所有网页
    connect(page,SIGNAL(sendpageurl(QString)),this,SLOT(receviveurl(QString)));
    page->setPage(page_number);
    int tab=ui->tabWidget->addTab(page,ui->textEdit->toPlainText());
    ui->tabWidget->setCurrentIndex(tab);//跳转到刚打开的页面
}
