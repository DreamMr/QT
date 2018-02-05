#include "myitem.h"
#include<QDebug>
#include<QGraphicsView>

MyItem::MyItem()
{
  setAcceptHoverEvents(true);
  cursor.setShape(Qt::PointingHandCursor);
}
void MyItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(cursor);
    form.setGeometry(event->screenPos().rx()+10,event->screenPos().ry(),233,217);
    form.setVisible(true);
}

void MyItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    form.setVisible(false);
}

void MyItem::setString(QString s)
{
    str=s;
}
MyItem::~MyItem()
{
  form.~Form();
}
