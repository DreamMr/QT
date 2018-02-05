#include "myview.h"
#include<QGraphicsItem>
#include<QDebug>
#include<QList>
#include<QGraphicsItemAnimation>
#include<math.h>
MyView::MyView(QWidget *parent):QGraphicsView(parent)
{
    //***********初始化
  dir[0][0]=0;dir[0][1]=1;//front
  dir[1][0]=0;dir[1][1]=-1;//back
  dir[2][0]=1;dir[2][1]=0;//down
  dir[3][0]=-1;dir[3][1]=0;//up
  step=0;
  setRow(3);
  win=false;
  messagebox.setIcon(QMessageBox::Information);
  messagebox.setText("Congratulations! Your win!");
  messagebox.setWindowTitle("Your win !");
}
//************设置矩阵的规模
void MyView::setRow(int r)
{
    row=r;
    location=new int *[row];
    for(int i=0;i<row;i++)
        location[i]=new int [row];
}
//***********鼠标点击更改矩阵状态
void MyView::mousePressEvent(QMouseEvent *event)
{
    if(!win)
    {
        emit sendPress(false);
        _high=height()/row;
        _width=width()/row;
        qDebug()<<height()<<width()<<"find";
         QTransform deviceTransform;
        QGraphicsItem *item=scene()->itemAt(mapToScene(event->pos()),deviceTransform );
         MyItem *_item=(MyItem *)item;
       QPoint point =mapFromScene(mapToScene(event->pos()));

       if(item && check(_item,point))//对item和item的位置进行检查并移动
       {
            step++;
            emit send(step);//发送步数
       }
    }
}

//***************更改矩阵的状态，交换位置
bool MyView::action(int _x, int _y, MyItem *item)
{
    item->setPos(item->pos().rx()+_x,item->pos().ry()+_y);
    QList<QGraphicsItem *> list=item->collidingItems();
      item->setPos(item->pos().rx()-_x,item->pos().ry()-_y);
    if(list.isEmpty())
    {
        item->setPos(item->pos().rx()+_x*_width,item->pos().ry()+_y*_high);
        int item_number=item->get_number();
        int item_x=item->get_x();
        int item_y=item->get_y();
        int tmp=location[item_x+_y][item_y+_x];
        location[item_x+_y][item_y+_x]=location[item_x][item_y];
        location[item_x][item_y]=tmp;
        item->set_location(item_x+_y,item_y+_x);
        qDebug()<<_x<<_y;
        qDebug()<<item_number;
        finish();
        return true;
    }
    return false;
}
//****判断是否获得胜利
bool MyView::finish()
{
    int num=0;bool flag=true;
    for(int i=0;i<row;i++)
        for(int j=0;j<row;j++)
            if(location[i][j]!=num++){//如果发现一个状态不对直接tiao跳出
                qDebug()<<location[i][j];flag=false;break;
            }
       if(flag)
       {
           qDebug()<<"WIN";
           win=true;
           messagebox.show();
       }
       else{
           qDebug()<<"not finish";
       }
    return true;
}
//*********检查item的位置合法性，只能朝四个方向移动
bool MyView::check(MyItem *item, QPoint point)
{
    for(int i=0;i<4;i++)
    {
        switch(i)
        {
           case 0:{
            if(point.rx()+_width>width())
             continue;
             break;
        }
          case 1:
          {
            if(point.rx()-_width<0)
              continue;
            break;
          }
        case 2:
        {
            if(point.ry()+_high>height())
               continue;
            break;
        }
        case 3:
        {
            if(point.ry()-_high<0)
               continue;
            break;
        }
        }
          if (action(dir[i][1],dir[i][0],item))//位置合法，交换位置
          {
              return true;
          }
    }
    return false;
}
