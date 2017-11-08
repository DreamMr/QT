#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "dialog_pre.h"
#include "dialog_premid.h"
#include "dialog.h"
//#include"mydock.h"
#include "binarytree.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QString s_pre;
    QString s_premid;
    BinaryTree<char> *tree;
private:
    Ui::Widget *ui;
    Dialog_pre *d_pre;
    Dialog_premid *d_pm;
    Dialog *dlg;
    char *change(QString tmp_s);
    void SwapTree(BinaryTreeNode<char> *current);
    bool open;
    void checkbutton();
 private slots:
    void receivedata(QString st);
    void receiveda(QString str_pre,QString str_mid);
    void on_pb_build_clicked();
    void on_pb_draw_clicked();
    void on_pb_find_clicked();
    void receivechar (char p);
    void on_pb_swap_clicked();

signals:
    void senddata(BinaryTree<char> *tree,double b);
};

#endif // WIDGET_H
