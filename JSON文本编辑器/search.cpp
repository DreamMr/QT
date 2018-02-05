#include "search.h"
#include "ui_search.h"

Search::Search(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);
    setVisible(false);
}

Search::~Search()
{
    delete ui;
}
//************鼠标点击查找按钮
void Search::on_pushButton_clicked()
{
    if(ui->radioButton->isChecked())//向前查找
    {
        emit  Find(0,ui->textEdit->toPlainText());
    }
    else if(ui->radioButton_2->isChecked())//向后查找
    {
        emit Find(1,ui->textEdit->toPlainText());
    }
}
//**************关闭按钮
void Search::on_pushButton_2_clicked()
{
    ui->textEdit->setPlainText("");
    close();
}
