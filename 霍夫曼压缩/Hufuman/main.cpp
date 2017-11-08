#include "mainwindow.h"
#include <QApplication>
#include<QTextCodec>
//#include<QFile>
//#include<QTextStream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    /* QFile file("test.txt");
     file.open(QIODevice::WriteOnly);
     int aaa=32;
     QString tmp="txt";
    // QTextStream ss(&file);
    // ss<<tmp;
    const char *p="txt";
     int num=file.write((char*)p,sizeof(char)*strlen(p));
     num=file.write((char*)&aaa,sizeof(aaa));
     file.close();
     QFile in("test.txt");
     in.open(QIODevice::ReadOnly);
     int aa=0;
     QString tt;
    // QTextStream s(&in);
    // s>>tt;
     char *tmp1=new char[256];
     tmp1[0]='\0';
     num=in.read((char*)tmp1,sizeof(char)*strlen(p));
     //tmp1[strlen(p)]='\0';
    num=in.read((char*)&aa,sizeof(int));
    int con=0;*/
   MainWindow w;
    w.setFixedSize(471,261);
    w.setWindowFlags(Qt::WindowCloseButtonHint);
    w.show();

    return a.exec();
}
