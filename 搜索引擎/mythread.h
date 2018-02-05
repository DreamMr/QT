#ifndef MYTHREAD_H
#define MYTHREAD_H
#include<QThread>
#include"search_engine.h"
class MyThread : public QThread
{
public:
    MyThread();
    void run();
    Search_engine *search;//搜索引擎对象
};

#endif // MYTHREAD_H
