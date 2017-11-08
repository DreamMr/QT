#include "mydock.h"
#include "ui_mydock.h"
#include<QPainter>
Mydock::Mydock(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::Mydock)
{
    ui->setupUi(this);
    setWindowTitle("Blackboard");
    draw=0;
}

void Mydock::receivedata(BinaryTree<char> *tree,double brol)
{
  t=tree;
  bro=brol;
  draw=true;
 // this->update();
}
char* Mydock::change(char p)
{
    char *s=new char [2];
    s[0]=p;
    s[1]='\0';
    return s;
}

void Mydock::paintEvent(QPaintEvent *event)//bro wei zichang
{
    QPainter painter(this);
    setPalette(QPalette(Qt::black));
    t->curreset();
    Queue<BinaryTreeNode<char> *>q;
    q.push(t->current);
    BinaryTreeNode<char> *cur=0;
    while(!q.isEmpty())
    {
        cur=q.front();
        q.pop();
        if(cur->LeftChild!=NULL)//判断条件不正确
        {
            if(cur->LeftChild->data!='#'){
                QPen pen(Qt::SolidLine);
                pen.setColor(Qt::white);
                painter.setPen(pen);
                painter.drawLine(QPoint(cur->point.x,cur->point.y+bro),QPoint(cur->LeftChild->point.x,cur->LeftChild->point.y));
                QRect rect(cur->point.x-bro/2,cur->point.y,bro,bro);
                painter.drawRect(rect);
                char *p=change(cur->data);
                QString str=p;//QString("%1").arg(p),
                painter.drawText(rect,Qt::AlignHCenter,str);
                q.push(cur->LeftChild);
                 delete p;
            }
            else{
                QRect rect(cur->point.x-bro/2,cur->point.y,bro,bro);
                QPen pen(Qt::SolidLine);
                 pen.setColor(Qt::white);
                painter.setPen(pen);
                painter.drawRect(rect);
                char *p=change(cur->data);
                QString str=p;//QString("%1").arg(p),
                painter.drawText(rect,Qt::AlignHCenter,str);
                q.push(cur->LeftChild);
                pen.setStyle(Qt::DashLine);
                painter.setPen(pen);
                painter.drawLine(QPoint(cur->point.x,cur->point.y+bro),QPoint(cur->LeftChild->point.x,cur->LeftChild->point.y));
                 delete p;
            }
        }
        else
        {
            QPen pen(Qt::DashLine);
             pen.setColor(Qt::white);
            painter.setPen(pen);
            QRect rect(cur->point.x-bro/2,cur->point.y,bro,bro);
           // painter.drawLine(QPoint(cur->point.x,cur->point.y+bro),QPoint(cur->LeftChild->point.x,cur->LeftChild->point.y));
            painter.drawRect(rect);
            char *p=change(cur->data);
            QString str=p;
            painter.drawText(rect,Qt::AlignHCenter,str);
            delete p;
        }
        if(cur->RightChild!= NULL )//没有连接父亲节点与有孩子
        {
            if(cur->RightChild->data!='#'){
                QPen pen(Qt::SolidLine);
                 pen.setColor(Qt::white);
                painter.setPen(pen);
            }
            else{
                QPen pen(Qt::DashLine); pen.setColor(Qt::white);
                painter.setPen(pen);
            }
            painter.drawLine(QPoint(cur->point.x,cur->point.y+bro),QPoint(cur->RightChild->point.x,cur->RightChild->point.y));
            q.push(cur->RightChild);
        }
    }
}

Mydock::~Mydock()
{
    delete ui;
}
