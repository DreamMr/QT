#include "urlitem.h"
#include<QCursor>
#include<QFont>
URLITEM::URLITEM(QGraphicsItem *parent):QGraphicsTextItem(parent)
{
    setAcceptHoverEvents(true);
}
//*********当鼠标点击搜索结果页面的item时发送item的url
void URLITEM::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit sendurl(url);
}
//**********当鼠标离开时把下划线去掉
void URLITEM::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QFont font;
    font=this->font();
    font.setUnderline(false);
    this->setFont(font);
}
//*************当鼠标放在item上时更改鼠标的手势，并添加下划线
void URLITEM::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QCursor cursor;
    cursor.setShape(Qt::PointingHandCursor);
    setCursor(cursor);
    setToolTip(url);
    QFont font;
    font=this->font();
    font.setUnderline(true);
    this->setFont(font);
}
