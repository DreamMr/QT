#include "widget.h"
#include "ui_widget.h"
#include<QScrollArea>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pb_build->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->pb_draw->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->pb_find->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->pb_swap->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");

    ui->dockWidget->setVisible(false);
    d_pre=new Dialog_pre(this);
    d_pm=new Dialog_premid(this);
    dlg=new Dialog(this);
    d_pre->setFixedSize(400,133);
    d_pm->setFixedSize(400,222);
    dlg->setFixedSize(206,120);
    connect(d_pre,SIGNAL(SendData(QString)),this,SLOT(receivedata(QString)));
    connect(d_pm,SIGNAL(senddata(QString,QString)),this,SLOT(receiveda(QString,QString)));
    connect(this,SIGNAL(senddata(BinaryTree<char> *,double)),ui->dockWidget,SLOT(receivedata(BinaryTree<char> *,double)));
    connect(dlg,SIGNAL(senddata(char)),this,SLOT(receivechar(char)));
    open=false;
    checkbutton();
}

char* Widget::change(QString tmp_s)
{
    QByteArray ba =tmp_s.toLatin1();
    char *p=ba.data();
    return p;
}

void Widget::checkbutton()
{
    if(open && tree->flag)
    {
        ui->pb_draw->setEnabled(true);
        ui->pb_find->setEnabled(true);
        ui->pb_swap->setEnabled(true);
        setWindowTitle("ReadData");
    }
    else
    {
        ui->pb_draw->setEnabled(false);
        ui->pb_find->setEnabled(false);
        ui->pb_swap->setEnabled(false);
        setWindowTitle("NoData");
    }
}

void Widget::receivedata(QString st)//接收前序
{
    s_pre=st;
    if(s_pre.length()>0){open=true;}
    QByteArray ba=s_pre.toLatin1();
    char *p=ba.data();
    int num=ui->comboBox->currentIndex();
    if(num==0)
    {
        tree=new BinaryTree<char>(1,p);
    }
    else if(num==1)
    {
        tree=new BinaryTree<char>(0,p);
    }
    checkbutton();
}

void Widget::receivechar(char p)
{
    tree->Find(p);
}

void Widget::receiveda(QString str_pre, QString str_mid)
{
    s_pre=str_pre;
    s_premid=str_mid;
    /*********
    非法输入改造

   *********/
    if(s_pre.length()>0 && s_premid.length()>0){open=true;}
    QByteArray ba=s_pre.toLatin1();
    char *p_pre=ba.data();
    //ba=s_premid.toLatin1();
    QByteArray ab=s_premid.toLatin1();
    char *p_mid=ab.data();
    tree=new BinaryTree<char>(p_pre,p_mid);
    checkbutton();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pb_build_clicked()
{
    int number=ui->comboBox->currentIndex();
    if(number==0)
    {
        d_pre->show();
    }
    else if(number==1)
    {
        d_pre->show();
    }
    else if(number==2)
    {
        d_pm->show();
    }
}



void Widget::on_pb_draw_clicked()
{
    Point point=tree->Graph(25,20,50);
    ui->dockWidget->setFixedSize(point.x+100,point.y+100);
    ui->dockWidget->setVisible(true);
    //scroarea.show();
    emit senddata(tree,25);
}

void Widget::on_pb_find_clicked()
{
   // tree->Find('B');
    dlg->show();
}

void Widget::on_pb_swap_clicked()
{
  tree->Swap();
}
