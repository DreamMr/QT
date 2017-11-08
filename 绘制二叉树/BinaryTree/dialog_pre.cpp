#include "dialog_pre.h"
#include "ui_dialog_pre.h"

Dialog_pre::Dialog_pre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_pre)
{
    ui->setupUi(this);
    ui->pb_ok->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->textEdit->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->textEdit->setPlainText("ABC##DE#G##F###");
    setWindowTitle("Pre_InPut");
}


Dialog_pre::~Dialog_pre()
{
    delete ui;
}

void Dialog_pre::on_pb_ok_clicked()
{
    emit SendData(ui->textEdit->toPlainText());
    close();
}
