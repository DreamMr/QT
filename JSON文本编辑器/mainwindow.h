#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<treewidgetitem.h>
//#include"mysyntaxhighlighter.h"
#include"search.h"
#include<QStack>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
   int CreateTree(QString s);
   // MySyntaxHighlighter *syn;
   int solve_Big (QString s,TreeWidgetItem *parent,int &i);
   int solve_middle(QString s,TreeWidgetItem *parent,int &i);
    void Change_Item(int colum,QString change);
   bool save_wirte(QString filename);
   void reset();
   int unsave();
   void open_data();
   QString origen;
private slots:
     void change_name();
     void change_value();
     void change_type(QString change);
    void on_tabWidget_tabBarClicked(int index);
   void on_actionExit_triggered();

   void on_actionSave_as_triggered();

   void on_actionSave_triggered();

   void on_actionNew_triggered();

   void on_actionOpen_triggered();

   void on_treeWidget_itemClicked(TreeWidgetItem *item, int column);

   void on_actionFind_triggered();
   void on_action_triggered();

   void on_action_2_triggered();

public slots:
   bool Find_re(int mode ,QString _string);
private:
    Ui::MainWindow *ui;
    Search *search;//查找界面
    int count;
    QString line_s;
    QString fileName;//打开的文件路径名

    int index;
    QString search_string;
    QStack<int>stack;//存储正则表达式的查询结果

    QStack<QChar>check_stack;//进行符号匹配的检查
};

#endif // MAINWINDOW_H
