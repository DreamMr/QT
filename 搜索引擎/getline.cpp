#include "getline.h"
#include<QDebug>
GETLINE::GETLINE()
{
    ptr=new char[2<<22];
}
//**********一次从磁盘中读取4m，每次返回一行的数据，若有数据返回为真，否则为假
bool GETLINE::getLine(QFile &in, string &tmp)
{
        if(list.size()>1)//若果缓存列表还有数据则直接赋值
        {
            QString t=list.first();
             list.pop_front();
            tmp=t.toStdString();
            return true;
        }
        else
        {
            if(list.size())//将不完整的数据交给leave
            {
                leave=list.first();list.pop_front();
            }
            else
            {
                leave.clear();
            }
        }
        if(!in.atEnd())//若果文件没读完
        {
            delete []ptr;
            ptr=new char[2<<22];
            int count=in.read(ptr,sizeof(char)*(2<<22));//从文件读取4m数据
            QString  t;t=QString(QLatin1String(ptr));
            qDebug()<<t;
            t=t.mid(0,count);//去除没用的数据
            qDebug()<<t;
            t=leave+t;//加上上一次的残余数据
            list=t.split('\n');
            QString re=list.first();
            list.pop_front();
            tmp=re.toStdString();
            return true;
        }
        if(leave.size())//如果文件到达末尾，但是leave是完整的数据，则返回leave
        {
            tmp=leave.toStdString();
            return true;
        }
        else
        return false;
}

