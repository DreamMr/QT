#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTextCursor>
#include"cal.h"
#include<math.h>
#include<QMessageBox>
#include<QClipboard>
#include"queue.h"
#define PI 3.1415926
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    right_kuo=false;
    left_kuo=true;
    number=true;
    yun=false;
    d_yun=true;
    point=true;
    sub=true;
    sub_op=false;
    num_k=0;
    t_tmp=false;
    ui->setupUi(this);
    ui->dockWidget->setVisible(false);
    check();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_find_clicked()
{
    if(t_tmp)
    {
        str+=")";
        t_tmp=false;
    }
    str+="#";
    show_s+="=";
    //k.push(show_s);
    cal c(str);
    double sum=0;
    sum=c.findout();
    if(c.err)
    {
        QMessageBox::warning(NULL,"运算错误","重新输入",QMessageBox::Ok,QMessageBox::Ok);
        show_s="";
        str="";
    }
    else
    {
        str="";
        str+=show_s+"\r\n";
        QString ans=show_s;
        //k.pop();
        ans+=QString::number(sum);
        //k.push(ans);
        show_value+=ans+"\r\n";
        str+=QString::number(sum);
    }
    ui->textEdit->setPlainText(str);
    str="";
    show_s="";
}

void MainWindow::on_num_0_clicked()
{
        str+="0";
        show_s+="0";
        ui->textEdit->setPlainText(show_s);
        right_kuo=true;
        left_kuo=false;
        number=true;
        yun=true;
        d_yun=false;
       // point=true;
        QString tmp=str.mid(str.length()-2,1);
        if(point)
        {
            point=true;
        }
        else if(tmp!=".")
        {
            point=true;
        }
        sub=false;
        sub_op=true;
        check();
}

void MainWindow::on_num_1_clicked()
{

    str+="1";
    show_s+="1";

    ui->textEdit->setPlainText(show_s);
    right_kuo=true;
    left_kuo=false;
    number=true;
    yun=true;
    d_yun=false;
    //point=true;
    QString tmp=str.mid(str.length()-2,1);
    if(point)
    {
        point=true;
    }
    else if(tmp!=".")
    {
        point=true;
    }
    sub=false;
    sub_op=true;
    check();
}

void MainWindow::on_num_2_clicked()
{

    str+="2";
    show_s+="2";
    //kuo=true;
    right_kuo=true;
    left_kuo=false;
    number=true;
    yun=true;
    d_yun=false;
    //point=true;
    QString tmp=str.mid(str.length()-2,1);
    if(point)
    {
        point=true;
    }
    else if(tmp!=".")
    {
        point=true;
    }
    sub=false;
    sub_op=true;
    check();
    ui->textEdit->setPlainText(show_s);
}

void MainWindow::on_num_3_clicked()
{

    str+="3";
    show_s+="3";
    //kuo=true;
    right_kuo=true;
    left_kuo=false;
    number=true;
    yun=true;
    d_yun=false;
    //point=true;
    QString tmp=str.mid(str.length()-2,1);
    if(point)
    {
        point=true;
    }
    else if(tmp!=".")
    {
        point=true;
    }
    sub=false;
    sub_op=true;
    check();
    ui->textEdit->setPlainText(show_s);
}

void MainWindow::on_num_4_clicked()
{
    //sub=false;
    str+="4";
    show_s+="4";
    //kuo=true;
    right_kuo=true;
    left_kuo=false;
    number=true;
    yun=true;
    d_yun=false;
   // point=true;
    QString tmp=str.mid(str.length()-2,1);
    if(point)
    {
        point=true;
    }
    else if(tmp!=".")
    {
        point=true;
    }
    sub=false;
    sub_op=true;
    check();
    ui->textEdit->setPlainText(show_s);
}

void MainWindow::on_num_5_clicked()
{
    //sub=false;
    str+="5";
    show_s+="5";
    //kuo=true;
    right_kuo=true;
    left_kuo=false;
    number=true;
    yun=true;
    d_yun=false;
   // point=true;
    QString tmp=str.mid(str.length()-2,1);
    if(point)
    {
        point=true;
    }
    else if(tmp!=".")
    {
        point=true;
    }
    sub=false;
    sub_op=true;
    check();
    ui->textEdit->setPlainText(show_s);
}

void MainWindow::on_num_6_clicked()
{
    //sub=false;
    str+="6";
    show_s+="6";
    //kuo=true;
    right_kuo=true;
    left_kuo=false;
    number=true;
    yun=true;
    d_yun=false;
    //point=true;
    QString tmp=str.mid(str.length()-2,1);
    if(point)
    {
        point=true;
    }
    else if(tmp!=".")
    {
        point=true;
    }
    sub=false;
    sub_op=true;
    check();
    ui->textEdit->setPlainText(show_s);
}

void MainWindow::on_num_7_clicked()
{
   // sub=false;
    str+="7";
    show_s+="7";
    //kuo=true;
    right_kuo=true;
    left_kuo=false;
    number=true;
    yun=true;
    d_yun=false;
    //point=true;
    QString tmp=str.mid(str.length()-2,1);
    if(point)
    {
        point=true;
    }
    else if(tmp!=".")
    {
        point=true;
    }
    sub=false;
    sub_op=true;
    check();
    ui->textEdit->setPlainText(show_s);
}

void MainWindow::on_num_8_clicked()
{
    //sub=false;
    str+="8";
    show_s+="8";
    //kuo=true;
    right_kuo=true;
    left_kuo=false;
    number=true;
    yun=true;
    d_yun=false;
   // point=true;
    QString tmp=str.mid(str.length()-2,1);
    if(point)
    {
        point=true;
    }
    else if(tmp!=".")
    {
        point=true;
    }
    sub=false;
    sub_op=true;
    check();
    ui->textEdit->setPlainText(show_s);
}

void MainWindow::on_num_9_clicked()
{
    //sub=false;
    str+="9";
    show_s+="9";
    //kuo=true;
    right_kuo=true;
    left_kuo=false;
    number=true;
    yun=true;
    d_yun=false;
    //point=true;
    QString tmp=str.mid(str.length()-2,1);
    if(point)
    {
        point=true;
    }
    else if(tmp!=".")
    {
        point=true;
    }
    sub=false;
    sub_op=true;
    check();
    ui->textEdit->setPlainText(show_s);
}

void MainWindow::on_num_point_clicked()
{
    //sub=false;
    str+=".";
    show_s+=".";
    ui->textEdit->setPlainText(show_s);
    right_kuo=false;
    left_kuo=false;
    number=true;
    yun=false;
    d_yun=false;
    point=false;
    sub=false;
    sub_op=false;
    check();
}

void MainWindow::on_num_add_clicked()
{
    if(t_tmp)
    {
        str+=")";
        t_tmp=false;
    }
    //sub=true;
    str+="+";
    show_s+="+";
    right_kuo=false;
    left_kuo=true;
    number=true;
    yun=false;
    d_yun=true;
    point=true;
    sub=true;
    sub_op=false;
    check();
    ui->textEdit->setPlainText(show_s);
}

void MainWindow::on_num_cheng_clicked()
{
    if(t_tmp)
    {
        str+=")";
        t_tmp=false;
    }
   // sub=true;
    str+="*";
    show_s+="*";
    right_kuo=false;
    left_kuo=true;
    number=true;
    yun=false;
    d_yun=true;
    point=true;
    sub=true;
    sub_op=false;
    check();
    ui->textEdit->setPlainText(show_s);
}

void MainWindow::on_num_chu_clicked()
{
    if(t_tmp)
    {
        str+=")";
        t_tmp=false;
    }
    sub=true;
    str+="/";
    show_s+="/";
    right_kuo=false;
    left_kuo=true;
    number=true;
    yun=false;
    d_yun=true;
    point=true;
    sub=true;
    sub_op=false;
    check();
    ui->textEdit->setPlainText(show_s);
}

void MainWindow::on_num_left_k_clicked()
{
    num_k++;
    sub=true;
    sub_op=false;
    str+="(";
    show_s+="(";
    QString tmp="(";
    tmp+=QString::number(num_k);
    point=false;
    yun=false;
    sub=true;
    zero=true;
    right_kuo=false;
    left_kuo=true;
    number=true;
    d_yun=true;
    ui->num_left_k->setText(tmp);
    ui->textEdit->setPlainText(show_s);
    check();
}

void MainWindow::on_num_right_k_clicked()
{

     if(num_k)
     {
        num_k--;
        str+=")";
        show_s+=")";
        QString tmp="(";
        if(num_k)
        {
            tmp+=QString::number(num_k);
            right_kuo=true;
        }
        left_kuo=false;
        point=false;
        sub_op=true;
        sub=false;
        number=false;
        yun=true;
        d_yun=false;
        zero=false;
        ui->num_left_k->setText(tmp);
        ui->textEdit->setPlainText(show_s);
        check();
    }

}

void MainWindow::on_num_sub_clicked()
{
    if(t_tmp)
    {
        str+=")";
        t_tmp=false;
    }
    if(sub)
    {
        str+="(0-";
        t_tmp=true;
    }
    else if(sub_op)
    {
        str+="-";
    }
    show_s+="-";
    //kuo=true;
    right_kuo=false;
    left_kuo=true;
    number=true;
    yun=false;
    d_yun=true;
    point=true;
    sub=false;
    sub_op=false;
    check();
     ui->textEdit->setPlainText(show_s);
}

void MainWindow::on_num_yu_clicked()
{
    if(t_tmp)
    {
        str+=")";
        t_tmp=false;
    }
    //sub=true;
    str+="%";
    show_s+="%";
   // kuo=true;
    right_kuo=false;
    left_kuo=true;
    number=true;
    yun=false;
    d_yun=true;
    point=true;
    sub=false;
    sub_op=false;
    check();
    ui->textEdit->setPlainText(show_s);
}

void MainWindow::on_num_c_clicked()
{
    show_s="";
    str="";
    //kuo=true;
    num_k=0;
    right_kuo=false;
    left_kuo=true;
    number=true;
    yun=false;
    d_yun=true;
    point=true;
    sub=true;
    sub_op=false;
    t_tmp=false;
    check();
    QString tmp_kk="(";
    ui->num_left_k->setText(tmp_kk);
    ui->textEdit->setPlainText(str);
}

void MainWindow::on_num_sin_clicked()
{
   show_s+="sin";
   str+="z";
   //kuo=false;
   right_kuo=false;
   left_kuo=false;
   number=true;
   yun=false;
   d_yun=false;
   point=false;
   sub=false;
   sub_op=true;
   check();
   ui->textEdit->setPlainText(show_s);
}

void MainWindow::on_num_cos_clicked()
{
    //kuo=false;
    show_s+="cos";
    str+="c";
    right_kuo=false;
    left_kuo=false;
    number=true;
    yun=false;
    d_yun=false;
    point=false;
    sub=false;
    sub_op=true;
    check();
    ui->textEdit->setPlainText(show_s);
}

void MainWindow::on_num_tan_clicked()
{
    //kuo=false;
    show_s+="tan";
    str+="t";
    right_kuo=false;
    left_kuo=false;
    number=true;
    yun=false;
    d_yun=false;
    point=false;
    sub=false;
    sub_op=true;
    check();
    ui->textEdit->setPlainText(show_s);
}

void MainWindow::on_num_pow_clicked()
{
    //kuo=false;
    show_s+="2^";
    str+="y";
    right_kuo=false;
    left_kuo=false;
    number=true;
    yun=false;
    d_yun=false;
    point=false;
    sub=false;
    sub_op=true;
    check();
    ui->textEdit->setPlainText(show_s);
}

void MainWindow::on_num_sqrt_clicked()
{
    //kuo=false;
    show_s+="sqrt";
    str+="s";
    right_kuo=false;
    left_kuo=false;
    number=true;
    yun=false;
    d_yun=false;
    point=false;
    sub=false;
    sub_op=true;
    check();
    ui->textEdit->setPlainText(show_s);
}

void MainWindow::on_num_pingfang_clicked()
{
    //show_s+=
}

void MainWindow::on_num_fen_x_clicked()
{
    //kuo=false;
    show_s+="1/";
    str+="a";
    right_kuo=false;
    left_kuo=false;
    number=true;
    yun=false;
    d_yun=false;
    point=false;
    sub=false;
    sub_op=true;
    check();
    ui->textEdit->setPlainText(show_s);
}

void MainWindow::on_num_left_clicked()
{
       QString tmp_s=str.mid(0,str.length()-1);
       QString tmp_c=str.mid(str.length()-1,1);
       str=tmp_s;

       if(tmp_c=="(")
       {
           num_k--;
           if(num_k)
           {
               right_kuo=true;
           }
           else
           {
               right_kuo=false;
           }
           left_kuo=true;
           QString tmp_kk="(";
           tmp_kk+=QString::number(num_k);
           ui->num_left_k->setText(tmp_kk);
           tmp_s=show_s.mid(0,show_s.length()-1);
           show_s=tmp_s;
           ui->textEdit->setPlainText(show_s);
       }
       else if(tmp_c==")")
       {
           num_k++;
           if(show_s[show_s.length()-1].toLatin1()>='0'&&show_s[show_s.length()-1].toLatin1()<='9')
           {
               if(point)
               point=true;
           }
           tmp_s=show_s.mid(0,show_s.length()-1);
           show_s=tmp_s;
           ui->textEdit->setPlainText(show_s);
       }
       else if(tmp_c=="+" || tmp_c=="-" || tmp_c=="*" || tmp_c=="/" || tmp_c=="%")
       {
           left_kuo=false;
           right_kuo=false;
           number=true;
           yun=true;
           d_yun=false;
           point=!point;
           sub=false;
           sub_op=true;
           tmp_s=show_s.mid(0,show_s.length()-1);
           show_s=tmp_s;
           ui->textEdit->setPlainText(show_s);
       }
       else if(tmp_c>="a" && tmp_c<="z")
       {
           right_kuo=false;
           left_kuo=true;
           number=true;
           yun=false;
           d_yun=true;
           point=false;
           sub=true;
           sub_op=false;
           if(tmp_c=="z" ||tmp_c=="c" || tmp_c=="t")
           {
               tmp_s=show_s.mid(0,show_s.length()-3);
           }
           else if(tmp_c=="a" || tmp_c=="y")
           {
               tmp_s=show_s.mid(0,show_s.length()-2);
           }
           else if(tmp_c=="s")
           {
               tmp_s=show_s.mid(0,show_s.length()-4);
           }
           show_s=tmp_s;
           ui->textEdit->setPlainText(show_s);
       }
       else if(tmp_c>="0" && tmp_c<="9")
       {
           QString tmp_cc=show_s.mid(show_s.length()-2,1);
           if(!(tmp_cc>="0" && tmp_cc<="9"))
           {
               yun=false;
           }
           tmp_s=show_s.mid(0,show_s.length()-1);
           show_s=tmp_s;
           ui->textEdit->setPlainText(show_s);
       }
       else if(tmp_c==".")
       {
           tmp_s=show_s.mid(0,show_s.length()-1);
           show_s=tmp_s;
           ui->textEdit->setPlainText(show_s);
           point =true;
           yun=true;

       }
           check();
}
void MainWindow::check()
{
    if(right_kuo)
    {
        ui->num_right_k->setEnabled(true);
    }
    else
    {
        ui->num_right_k->setEnabled(false);
    }
    if(left_kuo)
    {
        ui->num_left_k->setEnabled(true);
    }
    else
    {
        ui->num_left_k->setEnabled(false);
    }
    if(number)
    {
        ui->num_0->setEnabled(true);
        ui->num_1->setEnabled(true);
        ui->num_2->setEnabled(true);
        ui->num_3->setEnabled(true);
        ui->num_4->setEnabled(true);
        ui->num_5->setEnabled(true);
        ui->num_6->setEnabled(true);
        ui->num_7->setEnabled(true);
        ui->num_8->setEnabled(true);
        ui->num_9->setEnabled(true);
    }
    else
    {
         ui->num_0->setEnabled(false);
         ui->num_1->setEnabled(false);
         ui->num_2->setEnabled(false);
         ui->num_3->setEnabled(false);
         ui->num_4->setEnabled(false);
         ui->num_5->setEnabled(false);
         ui->num_6->setEnabled(false);
         ui->num_7->setEnabled(false);
         ui->num_8->setEnabled(false);
         ui->num_9->setEnabled(false);
    }
    if(yun)
    {
        ui->num_chu->setEnabled(true);
        ui->num_cheng->setEnabled(true);
        ui->num_sub->setEnabled(true);
        ui->num_add->setEnabled(true);
        ui->num_yu->setEnabled(true);
    }
    else
    {
        ui->num_chu->setEnabled(false);
        ui->num_cheng->setEnabled(false);
        ui->num_sub->setEnabled(false);
        ui->num_add->setEnabled(false);
        ui->num_yu->setEnabled(false);
    }
    if(d_yun)
    {
        ui->num_sin->setEnabled(true);
        ui->num_cos->setEnabled(true);
        ui->num_tan->setEnabled(true);
        ui->num_pow->setEnabled(true);
        ui->num_sqrt->setEnabled(true);
        ui->num_fen_x->setEnabled(true);
    }
    else
    {
        ui->num_sin->setEnabled(false);
        ui->num_cos->setEnabled(false);
        ui->num_tan->setEnabled(false);
        ui->num_pow->setEnabled(false);
        ui->num_sqrt->setEnabled(false);
        ui->num_fen_x->setEnabled(false);
    }
    if(point && yun)
    {
        ui->num_point->setEnabled(true);
    }
    else
    {
        ui->num_point->setEnabled(false);
    }
    if(sub || sub_op)
    {
        ui->num_sub->setEnabled(true);
    }
    else
    {
        ui->num_sub->setEnabled(false);
    }
}

void MainWindow::on_actionCopy_triggered()
{
    QClipboard *board=QApplication::clipboard();
    board->setText(ui->textEdit->toPlainText());
}

void MainWindow::on_actionPaste_triggered()
{
    QClipboard *board=QApplication::clipboard();
   show_s =board->text();
   ui->textEdit->setPlainText(show_s);
   str=show_s;
  // str+="#";
}

void MainWindow::on_me_clicked()
{

   /*if()
   {
       /*show_s+=k.front();
       k.pop();
       k.push(show_s);
       show_s+="\r\n";
       ui->dockWidget->setVisible(true);
       ui->textEdit_2->setPlainText(show_s);*/
  /* }
   else
   {
       QMessageBox::warning(NULL,"WARNING!","No Value",QMessageBox::Ok,QMessageBox::Ok);
   }*/
   ui->dockWidget->setVisible(true);
   ui->textEdit_2->setPlainText(show_value);
}
