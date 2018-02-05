#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPixmap>
#include<QPalette>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //***********初始化界面
    ui->setupUi(this);
    QPalette palette;
    QPixmap pixmap("bg.jpg");
     palette.setBrush(QPalette::Window, QBrush(pixmap));
     this->setPalette(palette);
     ui->pushButton->setStyleSheet("QPushButton{background-image: url(newgame.jpg);}");
     ui->pushButton_3->setStyleSheet("QPushButton{background-image: url(exit.jpg);}");
     this->setWindowTitle("大闹PUZZLE");
     sound=new QSound("bgm.wav",this);
     sound->play();
     setWindowIcon(QIcon("tubiao.ico"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
//*****开始游戏按钮
void MainWindow::on_pushButton_clicked()
{
    mode_nine=new nine(this);
    mode_nine->setAttribute(Qt::WA_DeleteOnClose);
    mode_nine->show();
}
//*********离开游戏按钮
void MainWindow::on_pushButton_3_clicked()
{
    sound->stop();
    delete sound;
    close();
}
