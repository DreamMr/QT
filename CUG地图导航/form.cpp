#include "form.h"
#include "ui_form.h"
#include<QPainter>
#include<QBrush>
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
   // this->setStyleSheet("QWidget{border-radius:15px;background-color:rgb(85,170,255)}");
    setWindowFlags(Qt::FramelessWindowHint);
    setVisible(false);
}

void Form::paintEvent(QPaintEvent *event)
{
   QPainter painter(this);
   painter.setBrush(QBrush(Qt::gray));
   painter.drawRoundedRect(0,0,width()-1,height()-1,20,20);
}

void Form::setup(QString r, QString t)
{
    text=t;
    pixmap=new QPixmap(r);
    ui->label->setPixmap(*pixmap);
    ui->label->setScaledContents(true);
    ui->label_2->setText(t);
}

Form::~Form()
{
    delete pixmap;
    delete ui;
}
