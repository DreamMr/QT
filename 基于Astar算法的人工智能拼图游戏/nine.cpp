#include "nine.h"
#include "ui_nine.h"
#include<QFileDialog>
#include<QDebug>
#include<QtGlobal>
#include<QTime>
#include<math.h>
#include<queue>
#include"a_star.h"
#define INF 0xffffff
nine::nine(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::nine)
{
    //*********设置窗体的外观以及对graohicsView的设置
    ui->setupUi(this);
    ui->graphicsView->setScene(&_player);
    ui->_visit->setScene(&_message);
   row=3;
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->_visit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->_visit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//********记录高宽
     height_sub=ui->graphicsView->height();
     width_sub=ui->graphicsView->width();
    height_sub=height_sub/row;
    width_sub=width_sub/row;
   connect(ui->graphicsView,SIGNAL(sendPress(bool)),this,SLOT(receivePress(bool)));
   connect(ui->graphicsView,SIGNAL(send(int)),this,SLOT(receive(int)));
   connect(&_time,SIGNAL(timeout()),this,SLOT(updataTime()));

   minute=0;
   sec=0;
   hour=0;
//**********初始化界面以及四个方向
   dir[0][0]=0;dir[0][1]=1;//front
   dir[1][0]=0;dir[1][1]=-1;//back
   dir[2][0]=1;dir[2][1]=0;//down
   dir[3][0]=-1;dir[3][1]=0;//up
   pixmapItem=NULL;
   picture_copy=NULL;
   this->setWindowTitle("大闹PUZZLE");
   ui->pushButton->setStyleSheet("border:2px groove gray;border-radius:10px");
   ui->pushButton_2->setStyleSheet("border:2px groove gray;border-radius:10px");
   ui->pushButton->setEnabled(false);
   ui->pushButton_2->setEnabled(true);
   setWindowIcon(QIcon("resource/tubiao.ico"));
}
//***********设置没有AI
void nine::receivePress(bool NOAI)
{
    ui->pushButton_2->setEnabled(NOAI);
}
//**********更新所花时间
void nine::updataTime()
{
    sec+=1;
    if(sec==60)
    {
        sec=0;
        minute+=1;
        if(minute==60)
        {
            minute=0;
            hour+=1;
        }
    }
    QString show=QString::number(hour)+":"+QString::number(minute)+":"+QString::number(sec);
    ui->lcdNumber->display(show);
}
//***********显示更新步数
void nine::receive(int step)
{
    ui->_score->setText(QString::number(step));
}

nine::~nine()
{
    if(pixmapItem)
    delete []pixmapItem;
    if(picture_copy)
    delete []picture_copy;
   delete ui;
}
//***********生成可解拼图
void nine::on_pushButton_clicked()
{
    //********初始化
    int _row=row;
    int _line=row;
    int *t_t=new int [row*row];int t_count=0;
  //  _thread.start();
    _time.start(1000);
    _player.clear();
    ui->_score->setText("0");
    qDebug()<<width_sub<<height_sub;
    tmp=new bool [row*row+1];
    for(int i=0;i<=row*row;i++)tmp[i]=0;
       qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
       int row_tmp=0,line=0;
       int i=0;
       int check=0;
//************生成可解拼图，保证目标状态于最初状态的逆序数对的奇偶性一致
       while(i<row*row)
       {
           int t=rand()%(row*row);

           if(!tmp[t])
           {
              ui->graphicsView->location[line][row_tmp]=t;
              t_t[t_count++]=t;
               if(row_tmp>=row-1){
                  row_tmp=0;
                   line++;
               }
               else{row_tmp++;}
               tmp[t]=1;
               i++;
           }
       }

     for(int i=_line*_line-2;i>=0;i--)
     {
         for(int j=0;j<=i;j++)
         {
             if(t_t[j]>t_t[i])
             {
                 qDebug()<<t_t[j]<<t_t[i];
                 check++;
             }
         }
     }
       if(check%2!=0)//如果奇偶性不一致，则更改倒数第二个和倒数第三个的位置
       {
           int tmp=ui->graphicsView->location[row-1][row-3];
          ui->graphicsView->location[row-1][row-3]=ui->graphicsView->location[row-1][row-2];
          ui->graphicsView->location[row-1][row-2]=tmp;
       }
       i=0;
       row_tmp=0;
       line=0;
       pixmapItem=new MyItem [row*row+1];
       tmp_Item=new int [row*row+1];
      while(i<(row*row))//放置图片
      {
          pixmapItem[i].setPixmap(picture_copy[ui->graphicsView->location[line][row_tmp]]);
          pixmapItem[i].setOffset(row_tmp*width_sub,line*height_sub);
          pixmapItem[i].set_number(ui->graphicsView->location[line][row_tmp]);
          tmp_Item[ui->graphicsView->location[line][row_tmp]]=i;
          pixmapItem[i].set_location(line,row_tmp);
          qDebug()<<row_tmp*width_sub<<line*height_sub;
          if(i<row*row-1){
          _player.addItem(& pixmapItem[i]);
          }
          i++;
          if(row_tmp>=row-1){row_tmp=0;line++;}
          else{row_tmp++;}
      }
     ui->graphicsView->finish();
     ui->pushButton->setEnabled(false);
}
//************将图片进行分割
void nine::copy_picture()
{
       int i=0;
       picture_copy=new QPixmap[row*row+1];
        for(int line=0;line<row;line++)
            for(int row_tmp=0;row_tmp<row;row_tmp++)
            {
                picture_copy[i]=pixmap.copy(row_tmp*width_sub,line*height_sub,width_sub,height_sub);
                i++;
            }
}
//***********打开图片的文件系统
void nine::on_action_triggered()
{
    QFileDialog filedialog;
    QPixmap p;
    QString picture_path=filedialog.getOpenFileName(this,"open picture","/","picture file(*.bmp;*.jpg;*.jpeg)");
    p.load(picture_path);
     pixmap=p.scaled(ui->graphicsView->width(),ui->graphicsView->height());//将图片适应位置
    _player.addPixmap(pixmap);
    _message.addPixmap( p.scaled(ui->_visit->width(),ui->_visit->height()));

    copy_picture();
    ui->pushButton->setEnabled(true);
}
void nine::sleep(unsigned int msec)
{
    QTime reachTime=QTime::currentTime().addMSecs(msec);

    while(QTime::currentTime()<reachTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}
//******用于执行A*算法的移动
void nine::action(int _x, int _y, MyItem *item)
{
    qDebug()<<item->pos();
      item->setPos(item->pos().rx()+_y*width_sub,item->pos().ry()+_x*height_sub);
}
//********执行A*算法
void nine::on_pushButton_2_clicked()//a*
{
    A_star star(row);
    int *t=new int [row*row+1];
    for(int i=0;i<row*row;i++)
        t[i]=i;
    A_node *a=new A_node( star.makeInt(ui->graphicsView->location),0,row-1,row-1,-1,-1,0,NULL);
    QStack<A_node>stack=star.A_search(a);
    int cur_x=row-1;
    int cur_y=row-1;
    int step=0;
    qDebug()<<stack.size();
    while(!stack.empty())
    {
        step++;
        ui->_score->setText(QString::number(step));
        A_node tmp=stack.top();
        stack.pop();
        int **map=star.makeMatrix(tmp.sum);
        action(cur_x-tmp.x,cur_y-tmp.y,&pixmapItem[t[tmp.x*row+tmp.y]]);
        int tt=  t[cur_x*row+cur_y];
        t[cur_x*row+cur_y]=t[tmp.x*row+tmp.y];
        t[tmp.x*row+tmp.y]=tt;
        sleep(800);
        cur_x=tmp.x;
        cur_y=tmp.y;
    }
    ui->graphicsView->messagebox.show();
}
//*******4*4
void nine::on_action_4_triggered()
{
   ui->graphicsView->setGeometry(ui->graphicsView->pos().rx(),ui->graphicsView->pos().ry(),952,684);
   row=4;
   width_sub=ui->graphicsView->width();
   width_sub=width_sub/row;
   height_sub=ui->graphicsView->height();
   height_sub=height_sub/row;
   ui->graphicsView->setRow(4);
   pixmap=pixmap.scaled(ui->graphicsView->width(),ui->graphicsView->height());
    copy_picture();
    ui->pushButton_2->setEnabled(false);
}
//*******5*5
void nine::on_action_5_triggered()
{
    ui->graphicsView->setGeometry(ui->graphicsView->pos().rx(),ui->graphicsView->pos().ry(),950,685);
    row=5;
    width_sub=ui->graphicsView->width();
    width_sub=width_sub/row;
    height_sub=ui->graphicsView->height();
    height_sub=height_sub/row;
    ui->graphicsView->setRow(5);
    pixmap=pixmap.scaled(ui->graphicsView->width(),ui->graphicsView->height());
     copy_picture();
     ui->pushButton_2->setEnabled(false);
}
