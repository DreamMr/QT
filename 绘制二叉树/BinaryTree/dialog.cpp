#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->pushButton->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->textEdit->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    setWindowTitle("Find");
}



Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    QByteArray ba=ui->textEdit->toPlainText().toLatin1();
    char *a=ba.data();
    emit senddata(a[0]);
    close();
}
