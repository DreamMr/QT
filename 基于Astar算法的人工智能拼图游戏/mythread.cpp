#include "mythread.h"

MyThread::MyThread(QObject *parent):QThread(parent)
{
    stopped=false;
    timer=new QTimer(this);
}


void MyThread::run()
{
      timer->start(1000);
    while(!stopped){}
}

void MyThread::stop()
{
    stopped=true;
}
