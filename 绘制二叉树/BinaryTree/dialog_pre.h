#ifndef DIALOG_PRE_H
#define DIALOG_PRE_H

#include <QDialog>

namespace Ui {
class Dialog_pre;
}

class Dialog_pre : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_pre(QWidget *parent = 0);
    ~Dialog_pre();

private:
    Ui::Dialog_pre *ui;

signals:
    void SendData(QString str);
private slots:
    void on_pb_ok_clicked();
};

#endif // DIALOG_PRE_H
