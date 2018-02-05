/********************************************************************************
** Form generated from reading UI file 'page.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGE_H
#define UI_PAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Page
{
public:
    QGraphicsView *graphicsView;
    QPushButton *pushButton;

    void setupUi(QWidget *Page)
    {
        if (Page->objectName().isEmpty())
            Page->setObjectName(QStringLiteral("Page"));
        Page->resize(1261, 431);
        graphicsView = new QGraphicsView(Page);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 1261, 381));
        pushButton = new QPushButton(Page);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(580, 390, 93, 28));

        retranslateUi(Page);

        QMetaObject::connectSlotsByName(Page);
    } // setupUi

    void retranslateUi(QWidget *Page)
    {
        Page->setWindowTitle(QApplication::translate("Page", "Form", 0));
        pushButton->setText(QApplication::translate("Page", "next page", 0));
    } // retranslateUi

};

namespace Ui {
    class Page: public Ui_Page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGE_H
