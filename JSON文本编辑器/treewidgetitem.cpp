#include "treewidgetitem.h"

TreeWidgetItem::TreeWidgetItem(QTreeWidgetItem *parent,QTreeWidgetItem *bro):QTreeWidgetItem(parent,bro)
{

}

TreeWidgetItem::TreeWidgetItem(QTreeWidget *parent):QTreeWidgetItem(parent)
{

}

void TreeWidgetItem::set_type(QString type)
{
    _type=type;
}
