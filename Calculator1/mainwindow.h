#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"queue.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     QString str;
     QString show_s;
     bool right_kuo;
     bool left_kuo;
     bool number;
     bool yun;
     bool d_yun;
     bool point;
     bool zero;
     bool sub;//singel
     bool sub_op;//double
     bool t_tmp;
     int num_k;
     //queue<QString> k;
     QString show_value;
private slots:
     void on_find_clicked();

     void on_num_0_clicked();

     void on_num_1_clicked();

     void on_num_2_clicked();

     void on_num_3_clicked();

     void on_num_4_clicked();

     void on_num_5_clicked();

     void on_num_6_clicked();

     void on_num_7_clicked();

     void on_num_8_clicked();

     void on_num_9_clicked();

     void on_num_point_clicked();

     void on_num_add_clicked();

     void on_num_cheng_clicked();

     void on_num_chu_clicked();

     void on_num_left_k_clicked();

     void on_num_right_k_clicked();

     void on_num_sub_clicked();

     void on_num_yu_clicked();

     void on_num_c_clicked();

     void on_num_sin_clicked();

     void on_num_cos_clicked();

     void on_num_tan_clicked();

     void on_num_pow_clicked();

     void on_num_sqrt_clicked();

     void on_num_pingfang_clicked();

     void on_num_fen_x_clicked();

     void on_num_left_clicked();

     void on_actionCopy_triggered();

     void on_actionPaste_triggered();

    // void on_pushButton_clicked();

     void on_me_clicked();

private:
    Ui::MainWindow *ui;
    void check();
};

#endif // MAINWINDOW_H
