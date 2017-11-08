#ifndef MYDOCK_H
#define MYDOCK_H

#include <QDockWidget>
#include "binarytree.h"
namespace Ui {
class Mydock;
}

class Mydock : public QDockWidget
{
    Q_OBJECT

public:
    explicit Mydock(QWidget *parent = 0);
    ~Mydock();
    void paintEvent(QPaintEvent *event);
private:
    Ui::Mydock *ui;
    bool draw;
    BinaryTree<char> *t;
    double bro;
private slots:
    void receivedata(BinaryTree<char> *tree,double brol);
    char* change(char p);
};

#endif // MYDOCK_H
