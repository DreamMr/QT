#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QProgressDialog>
#include"compression_nuw.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QString fileName;
    QString show_s;
    void sleep(unsigned int mesc);
    void coding(QString filename);
    Compression_nuw *c;
    QProgressDialog *pg;
    //void decoding(QString hufname);
    ~MainWindow();
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
private slots:
     void receivedata(int i);

     void on_action_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
