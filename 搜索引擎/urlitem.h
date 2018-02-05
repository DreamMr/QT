#ifndef URLITEM_H
#define URLITEM_H
#include<QGraphicsSceneMouseEvent>
#include<QGraphicsSceneHoverEvent>
#include<QGraphicsTextItem>
class URLITEM : public QGraphicsTextItem
{
     Q_OBJECT
public:
    URLITEM(QGraphicsItem *parent=NULL);
    void seturl(QString u){url=u;}
    QString geturl(){return url;}
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
   signals:
    void sendurl(QString url);
private:
    QString url;//存放当前item的url
};

#endif // URLITEM_H
