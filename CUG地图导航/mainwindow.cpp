#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QGraphicsRectItem>
#include<QRadioButton>
#include<QMouseEvent>
#include<QDebug>
#include<QScrollBar>
#include<QPainter>
#include<QGraphicsView>
#include<QMessageBox>
#include<QTextStream>
#include<QPen>
#include<QString>
#include<QGraphicsTextItem>
#define INF 0xfffff
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("resource/picture/xiaohui.ico"));
   //*******预处理**********
    sound=new QSound("resource/music/xiaoge.wav",this);
    sound->play();
    ui->graphicsView->setScene(&scene);
     connect(ui->graphicsView->slider,SIGNAL(valueChanged(int)),this,SLOT(receivevalue(int)));
    ui->graphicsView->setMouseTracking(true);
     ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    s=0;  e=0;
   map_point[1]=14;map_point[2]=21;map_point[3]=1;map_point[4]=17;map_point[5]=37;map_point[6]=12;map_point[7]=6;map_point[8]=8;map_point[9]=16;map_point[10]=26;
   map_point[11]=29;map_point[12]=30;map_point[13]=38;map_point[14]=10;map_point[15]=11;map_point[16]=19;
    pixmap.load("resource/picture/daohang.png");
    scene.addPixmap(pixmap);
   ui->graphicsView->show();
   zoom=50;
   state=0;
   //*******关闭滚动条*********
   ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

   //******读取绘制文字信息*********
    file=new QFile("resource/data/string.wwb");
   if(file->open(QIODevice::ReadWrite|QIODevice::Text))
   {
   QTextStream stream(file);
   for(int i=1;i<=16;i++)
   {
       stream>>ui->graphicsView->str[i];
       ui->graphicsView->text[i].setPlainText(ui->graphicsView->str[i]);
       ui->graphicsView->text[i].setPos(ui->graphicsView->point_tmp[map_point[i]]);
       scene.addItem(&ui->graphicsView->text[i]);
   }
   file->close();
   }

   //********绘制建筑的图形项**********
    QString temp;
    file=new QFile("resource/data/introduce.wwb");
    if(file->open(QIODevice::ReadWrite|QIODevice::Text))
    {
    QTextStream stream(file);
    for(int i=1;i<=16;i++)
    {
        stream>>temp;
       ellipse[i].setString(temp);
       ellipse[i].setBrush(QBrush(Qt::blue));
         ellipse[i].setRect(ui->graphicsView->point_tmp[map_point[i]].rx()-12,ui->graphicsView->point_tmp[map_point[i]].ry()-12,20,20);
         scene.addItem(&ellipse[i]);
         stream>>temp;
         ellipse[i].form.setup(temp,ellipse[i].str);
    }
    file->close();
    }
}
void MainWindow::clean()//清除路线
{
    while(!stack.isEmpty())
    {
        scene.removeItem(stack.top());
        stack.pop();
    }
}

void MainWindow::Dijstra(int s)//迪杰斯特拉算法
{
    //******返回立体图*****
    if(state)
        on_pushButton_5_clicked();

    //********算法主体*******
    for(int i=1;i<=39;i++)
    {
        used[i]=0;
        d[i]=INF;
        pre[i]=0;
    }
    d[s]=0;
    while(true)
    {
        int u=-1;
        for(int i=1;i<=39;i++)
        {
            if(!used[i] && (u==-1 || d[u]>d[i]))u=i;
        }
        if(u==-1)break;
        used[u]=true;
        for(int i=0;i<ui->graphicsView->v[u].size();i++)
        {
            if(d[ui->graphicsView->v[u][i].ver]>d[u]+ui->graphicsView->v[u][i].cost)
            {
                d[ui->graphicsView->v[u][i].ver]=d[u]+ui->graphicsView->v[u][i].cost;
                pre[ui->graphicsView->v[u][i].ver]=u;
            }
        }
    }

    //*********绘制线路*********
    int t=e;
    clean();//清除原始路线
    QGraphicsLineItem *line;
    while(pre[t])
    {
        line=new QGraphicsLineItem;
        QPen pen;
        pen.setColor(Qt::blue);
        pen.setStyle(Qt::DashLine);
        pen.setWidth(5);
        line->setPen(pen);
        line->setLine(ui->graphicsView->point_tmp[pre[t]].rx(),ui->graphicsView->point_tmp[pre[t]].ry(),ui->graphicsView->point_tmp[t].rx(),ui->graphicsView->point_tmp[t].ry());
       t=pre[t];
       scene.addItem(line);
       stack.push(line);
    }

}


void MainWindow::receivevalue(int value)//缩放
{
    qreal s;int i=1;
    if(zoom<value)
    {
        s=pow(1.01,value-zoom);
    }
    else
    {
        s=pow(1/1.01,zoom-value);
    }
    ui->graphicsView->scale(s,s);
    zoom=value;
}

MainWindow::~MainWindow()
{
   delete []ui->graphicsView->text;
    sound->stop();
    delete sound;
    delete ui;
}

void MainWindow::on_pushButton_clicked()//开始搜索
{
    s=map_point[ui->comboBox->currentIndex()];
    e=map_point[ui->comboBox_2->currentIndex()];
    if(s>0 && e>0)
    Dijstra(s);
    else
     QMessageBox::warning(NULL,"error","发生错误");
}

void MainWindow::on_pushButton_5_clicked()//图片转换
{
    if(!state)
    {
         pixmap.load("resource/picture/school.tif");
         item=scene.addPixmap(pixmap);
         ui->pushButton_5->setText("立体");
         state=1;
    }
    else
    {
         scene.removeItem(item);
         ui->pushButton_5->setText("卫星");
         state=0;
    }
}

void MainWindow::on_pushButton_2_clicked()//清除路线
{
    clean();
}

void MainWindow::on_pushButton_3_clicked()
{
    sound->stop();
}

void MainWindow::on_pushButton_4_clicked()
{
    sound->play();
}
