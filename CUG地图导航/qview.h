#ifndef QVIEW_H
#define QVIEW_H
#include<QGraphicsView>
#include<QMouseEvent>
#include<QObject>
#include<vector.h>
#include<fstream>
#include<QScrollBar>
#include<QToolTip>
#include<QSlider>
#include<QGraphicsTextItem>

using namespace  std;

struct edge
{
    int  cost;
    int pre;
    int ver;
    edge(int c=0,int p=0,int ve=0){cost=c;pre=p;ver=ve;}
};

class qview:public QGraphicsView
{
    Q_OBJECT

public:
   explicit qview(QWidget *parent = 0);
    QSlider *slider;//缩放的滑动条
   QPoint point_tmp[40];//存储路线中的点
   Vector<edge> v[40];//存储图
   fstream in;//读取文件
   QString str[17];//存放路标信息
   QGraphicsTextItem *text;//文本图形项
   int zoom;//缩放值
    void wheelEvent(QWheelEvent *event);//缩放
};

#endif // QVIEW_H
