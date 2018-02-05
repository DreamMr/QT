#ifndef NINE_H
#define NINE_H

#include <QMainWindow>
#include<QPixmap>
#include<QGraphicsScene>
#include<myitem.h>
#include<mythread.h>
#include<QTimer>
#include<QApplication>
#include<QTime>

namespace Ui {
class nine;
}

class nine : public QMainWindow
{
    Q_OBJECT

public:
    explicit nine(QWidget *parent = 0);
    ~nine();
  QPixmap *picture_copy;
  QGraphicsScene _player;
  QGraphicsScene _message;
  void copy_picture();
   QTimer _time;
   int *tmp_Item;
    MyItem *pixmapItem;
    void nine::sleep(unsigned int msec);

public slots:
  //void receiveItem(QGraphicsItem *item);
  void receive(int step);
   void updataTime();
   void receivePress(bool  NOAI);
private slots:
    void on_pushButton_clicked();

    void on_action_triggered();

    void on_pushButton_2_clicked();

    void on_action_4_triggered();

    void on_action_5_triggered();

private:
    Ui::nine *ui;
    bool *tmp;
    int empty;
    int dir[4][2];
      int height_sub;
      int width_sub;
      QPixmap pixmap;
    // MyThread _thread;
     int hour;
     int minute;
     int sec;
     void print();
     void change(int _x,int _y,int mode,int dir_x,int dir_y);
     void action(int _x,int _y,MyItem *item);
    int row;
};

#endif // NINE_H
