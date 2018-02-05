#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"search_page.h"
#include"page.h"
#include <QMainWindow>
#include"search_engine.h"
#include"mythread.h"
#include<QProgressDialog>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_tabWidget_tabCloseRequested(int index);
    void on_pushButton_clicked();
public slots:
    void receviveurl(QString url);
    void setCanVisiable();
private:
    Ui::MainWindow *ui;
    Search_engine *search;//搜索引擎主体
    SEARCH_PAGE *search_page;//打开网页的窗口
    Page *page;//搜索结果的显示窗口
    MyThread thread;//用于初始化的线程
    QProgressDialog *progress;//初始化的进度条
};

#endif // MAINWINDOW_H
