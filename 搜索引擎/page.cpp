#include "page.h"
#include "ui_page.h"
#include<QFile>
#include<QTextStream>
#include"QDebug"
#include<QList>
#define DISTANCE 15
Page::Page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    line=0;
    page_count=0;
}
//********设置搜索结果页面********
void Page::setPage( int page_numer)
{
    page_count=page_numer;
    on_pushButton_clicked();
}
//*********页面文本的排版********
/*大体思路：
 * 通过检验当前item所在位置是否与其他item发生碰撞，若发生碰撞则下移，直至不发生碰撞为止
 */
void Page::trans(URLITEM *item)
{
    QList<QGraphicsItem*> list;
    do
    {
        item->setPos(item->pos().rx(),item->pos().ry()+DISTANCE*line);
        list=item->collidingItems();
        line+=1;
    }while(list.size());
}
/*
int Page::LineNumber(QString info)
{
    int tmp=0;
    for(int i=0;i<info.size();i++)
    {
        if(info[i]=='\n')
            tmp++;
    }
    return tmp+1;
}
*/
//********发送url*********
void Page::receivepageurl(QString u)
{
    emit sendpageurl(u);
}

Page::~Page()
{
    delete ui;
}
//*********放置要显示的十个结果
void Page::on_pushButton_clicked()
{
    scene.clear();
    line=0;
    item=new URLITEM;
    item->setPlainText("Total search results: "+QString::number(page_count));
    scene.addItem(item);
   trans(item);
   int cou=0;//控制每页只有十个
   int size=v.size();//记录搜索结果的当前个数
    for(int i=size-1;i>=0 && cou<10;i--)
    {
        cou++;
        item=new URLITEM;
        item->seturl(QString::fromStdString(v[i].url.url));//设置url
        item->setPlainText(QString::fromStdString(v[i].url.url)+QString::fromStdString(v[i].url.infomation)+" score: "+QString::number(v[i].score));//设置显示的文本信息
        scene.addItem(item);
       trans(item);
     //  qDebug()<<QString::fromStdString(v[i].url);
        connect(item,SIGNAL(sendurl(QString)),this,SLOT(receivepageurl(QString)));
        v.pop_back();
    }
    if(v.empty())//如果结果数组为空则禁止点击下一页按钮
        ui->pushButton->setEnabled(false);
}
