#include "dialog_premid.h"
#include "ui_dialog_premid.h"
#include<QMessageBox>
Dialog_premid::Dialog_premid(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_premid)
{
    ui->setupUi(this);
    ui->pushButton->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->textEdit->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->textEdit_2->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->textEdit->setPlainText("ABDHIEJCFKGL");
    ui->textEdit_2->setPlainText("HDIBEJAFKCLG");
    setWindowTitle("Pre_Mid_InPut");
}

Dialog_premid::~Dialog_premid()
{
    delete ui;
}

bool Dialog_premid::Check(QString tmp_pre, QString tmp_mid)
{
  char pre[256];char mid[256];
  for(int i=0;i<256;i++)
  {
      pre[i]=0;
      mid[i]=0;
  }
  if(tmp_pre.length()!=tmp_mid.length())
  {
      return false;
  }
  else
  {
      for(int i=0;i<tmp_pre.length() || i<tmp_mid.length();i++)
      {
          if(i<tmp_pre.length())
          {
              pre[tmp_pre[i].toLatin1()]+=1;
          }
          if(i<tmp_mid.length())
          {
              mid[tmp_mid[i].toLatin1()]+=1;
          }
      }
      for(int i=0;i<256;i++)
      {
          if(pre[i]!=mid[i])
          {
              return false;
          }
      }
  }
  return true;
}

void Dialog_premid::on_pushButton_clicked()
{
    if(Check(ui->textEdit->toPlainText(),ui->textEdit_2->toPlainText()))
    {
        emit senddata(ui->textEdit->toPlainText(),ui->textEdit_2->toPlainText());
        close();
    }
    else
    {
        QMessageBox::warning(this,"error","String does not match",QMessageBox::Ok);
    }
}
