#include "myitem.h"
#include<QCursor>
#include<QList>
#include<QDebug>

MyItem::MyItem(QGraphicsPixmapItem *parent):QGraphicsPixmapItem(parent)
{
   _number=0;
   x=0;
   y=0;
}


