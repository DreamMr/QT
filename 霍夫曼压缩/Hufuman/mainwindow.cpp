#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDragEnterEvent>
#include<QDropEvent>
#include<QUrl>
#include<QFile>
#include<QMimeData>
#include<QTextStream>
#include<QFileDialog>
#include<QTextCodec>
#include<QTime>
#include<Windows.h>
//#include<QProgressDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
    c=new Compression_nuw;
    //code=new Dialog_code(this);
    //decode=new Dialog_decode(this);
    //connect(decode,SIGNAL(senddata(QString)),this,SLOT(receviedata(QString)));
    connect(c,SIGNAL(senddata(int)),this,SLOT(receivedata(int)));
    setAcceptDrops(true);
}
void MainWindow::sleep(unsigned int mesc)
{
    QTime timer=QTime::currentTime().addMSecs(mesc);
    while(QTime::currentTime()<timer)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

void MainWindow::receivedata(int i)
{
    pg->setValue(i);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
    else
    {
        event->ignore();
    }
}
/*void MainWindow::receviedata(QString temp)
{

}*/

void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData *mimedata=event->mimeData();
    if(mimedata->hasUrls())
    {
        QList<QUrl> urlList=mimedata->urls();
        fileName=urlList.at(0).toLocalFile();
        ui->textEdit->setPlainText(fileName);
        coding(fileName);
    }
}
void MainWindow::coding(QString filename)
{
    show_s=show_s+"文件路径:"+filename+"\r";
    int i=filename.length()-1;
    int k=0;

    for(;i>=0;i--)
    {
        if(filename[i].toLatin1()=='.')
          { k=i;}
        else if(filename[i].toLatin1()=='/')
        {
                break;
        }
     }
    QString tmp_front=filename.mid(0,k);
    QString tmp=filename.mid(k,filename.length()-k);
    QString file_name=filename.mid(i+1,k-i-1);
    if(tmp==".huf")
    {
        //jieya
        QString choose="已选择文件路径:";
        QString show_tmp=QFileDialog::getSaveFileName(this,"save as",file_name);
        if(!show_tmp.isNull())
        {
            show_s=show_s+choose+show_tmp+"\r";
            tmp_front=show_tmp;
        }
        else
        {
            show_s=show_s+choose+show_tmp+"\r";
        }
        show_s=show_s+"解压中请等待..."+"\n";
        ui->textEdit->setPlainText(show_s);
        pg=new QProgressDialog(this);
        pg->setRange(0,100);
       // pg->setWindowFlags(Qt::WindowCloseButtonHint);
        pg->setValue(0);
        pg->setLabelText(tr("解压中请等待..."));
        pg->show();
        sleep(200);
       c->Compression_start(tmp_front,filename,0);
       sleep(200);
       show_s=show_s+"解压成功!"+"\n";
       ui->textEdit->setPlainText(show_s);
    }
    else
    {
        //yasuo
        QString choose="已选择文件路径:";
        QString opf=tmp_front+".huf";
        QString show_tmp=QFileDialog::getSaveFileName(this,"save as",file_name);
        if(!show_tmp.isNull())
        {
            show_s=show_s+choose+show_tmp+"\r";
           // filename=show_tmp;
            opf=show_tmp+".huf";
        }
        else
        {
            show_s=show_s+choose+show_tmp+"\r";
        }
        show_s=show_s+"压缩中请等待..."+"\n";
        ui->textEdit->setPlainText(show_s);
        pg=new QProgressDialog(this);
        pg->setRange(0,100);
        pg->setLabelText(tr("压缩中请等待..."));
        pg->setFixedSize(300,150);
        //pg->setWindowFlags(Qt::WindowCloseButtonHint);
        pg->setValue(0);
        pg->show();
        sleep(200);
       double ans=c->Compression_start(filename,opf);
         sleep(200);
        show_s=show_s+"压缩成功!"+"\n";
        QString ans_tmp=QString::number(ans);
        show_s=show_s+"压缩比为:"+ans_tmp+"%"+"\n";
        ui->textEdit->setPlainText(show_s);
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
    ShellExecute(NULL, L"open", L"ReadMe.txt", NULL, NULL, SW_SHOWNORMAL);
}
