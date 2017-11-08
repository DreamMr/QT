#ifndef DIALOG_PREMID_H
#define DIALOG_PREMID_H

#include <QDialog>

namespace Ui {
class Dialog_premid;
}

class Dialog_premid : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_premid(QWidget *parent = 0);
    ~Dialog_premid();
     bool Check(QString tmp_pre,QString tmp_mid);
private:
    Ui::Dialog_premid *ui;
signals:
    void senddata(QString str_pre,QString str_mid);
 private slots:
    void on_pushButton_clicked();
};

#endif // DIALOG_PREMID_H
