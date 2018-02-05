#ifndef TREEWIDGETITEM_H
#define TREEWIDGETITEM_H
#include<QTreeWidgetItem>

class TreeWidgetItem : public QTreeWidgetItem
{
public:
    TreeWidgetItem(QTreeWidgetItem *parent=NULL,QTreeWidgetItem *bro=NULL);
    TreeWidgetItem(QTreeWidget *parent=NULL);
    void set_type(QString type);
    QString Get_type(){return _type;}
private:
    QString _type;
};

#endif // TREEWIDGETITEM_H
