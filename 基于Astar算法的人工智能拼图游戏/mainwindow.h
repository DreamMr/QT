#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QSound>
#include <QMainWindow>
#include<nine.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
  nine *mode_nine;//九宫格界面
  QSound *sound;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
