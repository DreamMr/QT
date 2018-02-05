#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QGraphicsItem>
#include <QMainWindow>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QGraphicsPixmapItem>
#include<QFile>
#include<QStack>
#include<qview.h>
#include<myitem.h>
#include<QSound>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QGraphicsScene scene;//场景
    QGraphicsPixmapItem *item;//存放卫星图
    ~MainWindow();
    QPixmap pixmap;//存放立体图
    void Dijstra(int s);
    int map_point[16];//建立表方便查找
    int s;//源点
    int e;//终点
    int d[40];//存储迪杰斯特拉最近距离
    bool used[40];//迪杰斯特拉辅助数组
    int pre[40];//记录每条最短路点的前驱节点
    int state;//立体图与卫星图状态判断
    int zoom;//存储滑动条的值
    MyItem ellipse[17];//路标图形项
    QFile *file;//读取文件
    QSound *sound;
   QStack<QGraphicsLineItem *> stack;//保存绘制路线的栈
private slots:
    void on_pushButton_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

public slots:
   void receivevalue(int value);
private:
   void clean();
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
