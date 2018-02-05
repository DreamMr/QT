#ifndef GETLINE_H
#define GETLINE_H

#include<QString>
#include<QFile>
#include<QStringList>
#include<string>
using namespace std;
//************
//缓存类：在进行读文件时每次先从文件中读取4m存入一个字符串中，在将字符串进行分割
//************
class GETLINE
{
public:
    GETLINE();
    ~GETLINE()
    {
        delete ptr;
    }
    bool getLine(QFile &in,string &tmp);
private:
    char *ptr;//用于读取文件
    QString leave;//存储不是完整的数据和下次的数据一起作为完整的数据
    QStringList list;//将所读的文件进行分割，每一块为一行
};

#endif // GETLINE_H
