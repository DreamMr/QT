#include"qview.h"
#include<QDebug>
#include<math.h>
qview:: qview(QWidget *parent):QGraphicsView(parent)
    {
    //***********预处理************
        text=new QGraphicsTextItem[17];
        zoom=2;
        v[1].push_back(edge(1,0,2)); v[1].push_back(edge(5,0,39));
        v[2].push_back(edge(1,0,1));v[2].push_back(edge(2,0,3));
        v[3].push_back(edge(2,0,2));v[3].push_back(edge(3,0,4));
        v[4].push_back(edge(3,0,3));v[4].push_back(edge(5,0,5));v[4].push_back(edge(5,0,12));
        v[5].push_back(edge(1,0,6));v[5].push_back(edge(5,0,4));
        v[6].push_back(edge(1,0,5));v[6].push_back(edge(15,0,7));
        v[7].push_back(edge(3,0,8));v[7].push_back(edge(15,0,6));
        v[8].push_back(edge(3,0,7));v[8].push_back(edge(2,0,9));
        v[9].push_back(edge(2,0,8));v[9].push_back(edge(2,0,10));v[9].push_back(edge(3,0,37));
        v[10].push_back(edge(2,0,9));v[10].push_back(edge(6,0,11));
        v[11].push_back(edge(6,0,10));v[11].push_back(edge(12,0,12));
        v[12].push_back(edge(2,0,11));v[12].push_back(edge(4,0,13));v[12].push_back(edge(5,0,4));
        v[13].push_back(edge(4,0,12));v[13].push_back(edge(1,0,14));v[13].push_back(edge(3,0,15));
        v[14].push_back(edge(1,0,13));
        v[15].push_back(edge(3,0,13));v[15].push_back(edge(8,0,16));v[15].push_back(edge(2,0,17));v[15].push_back(edge(10,0,39));
        v[16].push_back(edge(8,0,15));
        v[17].push_back(edge(2,0,15));v[17].push_back(edge(2,0,18));
        v[18].push_back(edge(2,0,17));v[18].push_back(edge(5,0,19));v[18].push_back(edge(8,0,35));
        v[19].push_back(edge(3,0,20));v[19].push_back(edge(5,0,18));
        v[20].push_back(edge(3,0,19));v[20].push_back(edge(2,0,21));v[20].push_back(edge(4,0,33));
        v[21].push_back(edge(2,0,20));v[21].push_back(edge(5,0,22));
        v[22].push_back(edge(5,0,21));v[22].push_back(edge(9,0,23));v[22].push_back(edge(20,0,28));
        v[23].push_back(edge(9,0,22));v[23].push_back(edge(20,0,24));
        v[24].push_back(edge(20,0,23));v[24].push_back(edge(17,0,25));
        v[25].push_back(edge(17,0,24));v[25].push_back(edge(20,0,27));v[25].push_back(edge(2,0,26));
        v[26].push_back(edge(2,0,25));
        v[27].push_back(edge(20,0,25));v[27].push_back(edge(10,0,28));
        v[28].push_back(edge(10,0,27));v[28].push_back(edge(8,0,38));v[28].push_back(edge(8,0,29));v[28].push_back(edge(20,0,22));
        v[29].push_back(edge(2,0,31));v[29].push_back(edge(8,0,28));v[29].push_back(edge(2,0,30));
        v[30].push_back(edge(2,0,29));
        v[31].push_back(edge(2,0,29));v[31].push_back(edge(2,0,32));v[31].push_back(edge(5,0,34));
        v[32].push_back(edge(7,0,33));v[32].push_back(edge(2,0,31));
        v[33].push_back(edge(7,0,32));v[33].push_back(edge(4,0,20));
        v[34].push_back(edge(5,0,31));v[34].push_back(edge(6,0,35));v[34].push_back(edge(8,0,36));
        v[35].push_back(edge(6,0,34));v[35].push_back(edge(8,0,18));
        v[36].push_back(edge(8,0,34));v[36].push_back(edge(6,0,37));
        v[37].push_back(edge(6,0,36));v[37].push_back(edge(3,0,9));
        v[38].push_back(edge(8,0,28));
        v[39].push_back(edge(5,0,1));v[39].push_back(edge(10,0,15));

        //***********设置滑动条的初始值
        slider=new QSlider(this);
        slider->setOrientation(Qt::Vertical);
        slider->setGeometry(30,45,20,250);
        slider->setRange(1,100);
        slider->setTickInterval(10);
        slider->setValue(50);
        slider->show();

        //********从文件中读取点的坐标
        in.open("resource/data/input.wwb",ios_base::in);
        for(int i=1;i<=39;i++)
        {
            int tmp=0;in>>tmp;
            point_tmp[i].setX(tmp);
            in>>tmp;
            point_tmp[i].setY(tmp);
        }
        in.close();
    }
  void qview::wheelEvent(QWheelEvent *event)
  {
      if(event->delta()>0)
      {
          if(zoom<4)
          {
              zoom++;
              slider->setValue(zoom*25);
          }
      }
      else
      {
          if(zoom>0)
          {
              zoom--;
              slider->setValue(zoom*25);
          }
      }
  }

