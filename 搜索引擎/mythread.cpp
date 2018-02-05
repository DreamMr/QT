#include "mythread.h"

MyThread::MyThread()
{

}
//******在线程中完成对search的初始化
void MyThread::run()
{
    if(search)
    {
        search->Start();
    }
}
