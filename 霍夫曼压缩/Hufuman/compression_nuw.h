#ifndef COMPRESSION_NUW_H
#define COMPRESSION_NUW_H

#include <QObject>
#include<iostream>
#include<math.h>
#include<QFile>
#include<QByteArray>
#include"huffmantree.h"
#include<QFileInfo>
#include"heap.h"
//#include"info.h"
using namespace std;
class Info
{
public:
    Info() { len = 0; value = 0; count = 0; }
    unsigned char ch;
    char *p;
    int len;//the length of p
    int value;//the value of p
    long long count;
    bool operator<(Info i) { return count < i.count; }
    bool operator>(Info i) { return count > i.count; }
    Info operator =(Info &i)
    {
        ch = i.ch;
        len = i.len;
        value = i.value;
        count = i.count;
        return *this;
    }
};
class Compression_nuw : public QObject
{
    Q_OBJECT
public:
    explicit Compression_nuw(QObject *parent = 0);
    double Compression_start(QString openfile,QString savefile);
    void Compression_start(QString saveposition,QString openposition,int i);
    void CreateInfo();//得到基本的创建树
    double Coding();//压缩函数
    void Decoding(QFile &in,QString save);//解压函数
    void PreOrder(BinaryTreeNode<long long> *current, char *a);
    int setvalue(char *a);
    char *addch(char *a, char tmp);
    int Addtail(char *p, int start, int end);
    QString Addfile(QString p);
    char* AddCHAR(char *p1, char *p2);
signals:
    void senddata(int i);
private:
    Info aInfo[256];//根据ascii码存储
    Info *bInfo;
    int size;//文件中的字符种类
    HuffmanTree<long long> tree;
    QString savefile;
    QString openfile;
    long long file_size;

};

#endif // COMPRESSION_NUW_H
