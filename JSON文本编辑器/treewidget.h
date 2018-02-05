#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QObject>
#include<QWidget>
#include<QTreeWidget>
#include"treewidgetitem.h"
#include<QMouseEvent>
#include<QDebug>
class TreeWidget : public QTreeWidget
{
       Q_OBJECT
public:
    TreeWidget(QWidget *parent);
    void mouseReleaseEvent(QMouseEvent *event);
 signals:
    void itemClicked(TreeWidgetItem *item,int colum);
};

#endif // TREEWIDGET_H
