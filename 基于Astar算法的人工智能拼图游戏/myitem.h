#ifndef MYITEM_H
#define MYITEM_H

#include<QGraphicsPixmapItem>
#include<QPixmap>
#include<QMouseEvent>
//#include<QObject>
class MyItem : public QGraphicsPixmapItem
{
     //Q_OBJECT
public:
 MyItem(QGraphicsPixmapItem *parent=NULL);
 ~MyItem()
 {

 }
  void set_number(int num){_number=num;}
  void set_location(int _x,int _y){x=_x;y=_y;}
  int get_number(){return _number;}
  int get_x(){return x;}
  int get_y(){return y;}
private:
    int _number;
    int x;
    int y;
};

#endif // MYITEM_H
