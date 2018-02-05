#ifndef MYTHREAD_H
#define MYTHREAD_H

#include<QThread>
#include<QTimer>
#include<QDateTime>
class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread(QObject *parent=NULL);
    void stop();
     QTimer *timer;
protected:
    void run();
private:
    volatile bool stopped;

public slots:
};

#endif // MYTHREAD_H
