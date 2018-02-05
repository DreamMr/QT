#include "treewidget.h"

TreeWidget::TreeWidget(QWidget *parent):QTreeWidget(parent)
{

}
//*************鼠标点击发送当前选中的item
void TreeWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        emit itemClicked((TreeWidgetItem *)this->currentItem(),this->currentColumn());
    }
}


