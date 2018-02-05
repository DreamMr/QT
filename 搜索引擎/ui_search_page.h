/********************************************************************************
** Form generated from reading UI file 'search_page.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCH_PAGE_H
#define UI_SEARCH_PAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SEARCH_PAGE
{
public:

    void setupUi(QWidget *SEARCH_PAGE)
    {
        if (SEARCH_PAGE->objectName().isEmpty())
            SEARCH_PAGE->setObjectName(QStringLiteral("SEARCH_PAGE"));
        SEARCH_PAGE->resize(1297, 486);

        retranslateUi(SEARCH_PAGE);

        QMetaObject::connectSlotsByName(SEARCH_PAGE);
    } // setupUi

    void retranslateUi(QWidget *SEARCH_PAGE)
    {
        SEARCH_PAGE->setWindowTitle(QApplication::translate("SEARCH_PAGE", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class SEARCH_PAGE: public Ui_SEARCH_PAGE {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCH_PAGE_H
