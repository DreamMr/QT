#ifndef MYITEM_H
#define MYITEM_H
#include<QGraphicsSceneHoverEvent>
#include<QGraphicsEllipseItem>
#include<QCursor>
#include<form.h>
class MyItem : public QGraphicsEllipseItem
{
public:
    MyItem();
    ~MyItem();
    void hoverEnterEvent(QGraphicsSceneHoverEvent *);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);
    void setString(QString s);
    QString str;
    QCursor cursor;
    Form  form;
};

#endif // MYITEM_H
