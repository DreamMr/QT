#ifndef MYVIEW_H
#define MYVIEW_H

#include <QObject>
#include<QGraphicsView>
#include<QMouseEvent>
#include"myitem.h"
#include<QMessageBox>
class MyView : public QGraphicsView
{
    Q_OBJECT
public:
    MyView(QWidget *parent=NULL);
    QMessageBox messagebox;//获胜信息框
    ~MyView()
    {

    }
    void mousePressEvent(QMouseEvent *event);
    int step;//记录玩家的步数
     int **location;//九宫格矩阵
     bool finish();//检测是否完成
     bool win;
     bool action(int _x,int _y,MyItem *item);
     void setRow(int r);
        int row;
signals:
    void send(int step);
    void sendStep(int _x,int _y);
    void sendPress(bool NOAI);
private:
    int dir[4][2];
    int _high;//一个格子的高度
    int _width;//一个格子的宽度
    bool check(MyItem *item,QPoint point);

};

#endif // MYVIEW_H
