/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <qview.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    qview *graphicsView;
    QPushButton *pushButton_5;
    QLabel *label_3;
    QLabel *label_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget_2;
    QWidget *dockWidgetContents_4;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *comboBox_2;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QLabel *label_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1180, 557);
        MainWindow->setStyleSheet(QLatin1String("QMainWindow{\n"
"border - radius:25px;\n"
"}"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new qview(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 1021, 491));
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(10, 330, 51, 28));
        pushButton_5->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_5->setToolTipDuration(0);
        pushButton_5->setStyleSheet(QStringLiteral(""));
        pushButton_5->setFlat(true);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 20, 20, 20));
        label_3->setToolTipDuration(0);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 310, 16, 16));
        label_4->setToolTipDuration(0);
        MainWindow->setCentralWidget(centralWidget);
        graphicsView->raise();
        pushButton_5->raise();
        label_4->raise();
        label_3->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1180, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        dockWidget_2 = new QDockWidget(MainWindow);
        dockWidget_2->setObjectName(QStringLiteral("dockWidget_2"));
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QStringLiteral("dockWidgetContents_4"));
        gridLayout = new QGridLayout(dockWidgetContents_4);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(dockWidgetContents_4);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBox_2 = new QComboBox(dockWidgetContents_4);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        gridLayout->addWidget(comboBox_2, 1, 1, 1, 2);

        comboBox = new QComboBox(dockWidgetContents_4);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 0, 1, 1, 2);

        pushButton = new QPushButton(dockWidgetContents_4);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 2, 0, 1, 2);

        label_2 = new QLabel(dockWidgetContents_4);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        pushButton_2 = new QPushButton(dockWidgetContents_4);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 2, 2, 1, 1);

        pushButton_3 = new QPushButton(dockWidgetContents_4);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 3, 0, 1, 2);

        pushButton_4 = new QPushButton(dockWidgetContents_4);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 3, 2, 1, 1);

        dockWidget_2->setWidget(dockWidgetContents_4);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_2);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\346\210\221\347\210\261\345\234\260\345\244\247\344\271\213\346\240\241\345\233\255\345\257\274\350\210\252", 0));
#ifndef QT_NO_TOOLTIP
        pushButton_5->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pushButton_5->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        pushButton_5->setText(QApplication::translate("MainWindow", "\345\215\253\346\230\237", 0));
        label_3->setText(QApplication::translate("MainWindow", "+", 0));
        label_4->setText(QApplication::translate("MainWindow", "-", 0));
        label->setText(QApplication::translate("MainWindow", "\345\247\213\345\217\221\345\234\260", 0));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "\344\275\223\350\202\262\351\246\206", 0)
         << QApplication::translate("MainWindow", "\346\225\231\344\270\200\346\245\274", 0)
         << QApplication::translate("MainWindow", "\346\225\231\344\272\214\346\245\274", 0)
         << QApplication::translate("MainWindow", "\346\225\231\344\270\211\346\245\274", 0)
         << QApplication::translate("MainWindow", "#52#53\346\240\213", 0)
         << QApplication::translate("MainWindow", "\345\205\254\344\270\273\346\245\274", 0)
         << QApplication::translate("MainWindow", "\345\255\246\347\224\237\344\270\200\351\243\237\345\240\202", 0)
         << QApplication::translate("MainWindow", "\345\255\246\347\224\237\344\270\211\351\243\237\345\240\202", 0)
         << QApplication::translate("MainWindow", "\344\277\241\346\201\257\346\245\274", 0)
         << QApplication::translate("MainWindow", "\344\277\241\345\267\245\346\245\274", 0)
         << QApplication::translate("MainWindow", "\345\233\276\344\271\246\351\246\206", 0)
         << QApplication::translate("MainWindow", "\346\226\260\345\263\260\345\205\254\345\257\223", 0)
         << QApplication::translate("MainWindow", "\345\215\232\347\211\251\351\246\206", 0)
         << QApplication::translate("MainWindow", "\351\270\277\346\257\205\345\240\202", 0)
         << QApplication::translate("MainWindow", "\345\244\247\345\255\246\347\224\237\346\264\273\345\212\250\344\270\255\345\277\203", 0)
         << QApplication::translate("MainWindow", "\344\270\273\346\245\274", 0)
        );
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "\344\275\223\350\202\262\351\246\206", 0)
         << QApplication::translate("MainWindow", "\346\225\231\344\270\200\346\245\274", 0)
         << QApplication::translate("MainWindow", "\346\225\231\344\272\214\346\245\274", 0)
         << QApplication::translate("MainWindow", "\346\225\231\344\270\211\346\245\274", 0)
         << QApplication::translate("MainWindow", "#52#53\346\240\213", 0)
         << QApplication::translate("MainWindow", "\345\205\254\344\270\273\346\245\274", 0)
         << QApplication::translate("MainWindow", "\345\255\246\347\224\237\344\270\200\351\243\237\345\240\202", 0)
         << QApplication::translate("MainWindow", "\345\255\246\347\224\237\344\270\211\351\243\237\345\240\202", 0)
         << QApplication::translate("MainWindow", "\344\277\241\346\201\257\346\245\274", 0)
         << QApplication::translate("MainWindow", "\344\277\241\345\267\245\346\245\274", 0)
         << QApplication::translate("MainWindow", "\345\233\276\344\271\246\351\246\206", 0)
         << QApplication::translate("MainWindow", "\346\226\260\345\263\260\345\205\254\345\257\223", 0)
         << QApplication::translate("MainWindow", "\345\215\232\347\211\251\351\246\206", 0)
         << QApplication::translate("MainWindow", "\351\270\277\346\257\205\345\240\202", 0)
         << QApplication::translate("MainWindow", "\345\244\247\345\255\246\347\224\237\346\264\273\345\212\250\344\270\255\345\277\203", 0)
         << QApplication::translate("MainWindow", "\344\270\273\346\245\274", 0)
        );
        pushButton->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\346\220\234\347\264\242", 0));
        label_2->setText(QApplication::translate("MainWindow", "\347\273\210\347\202\271\347\253\231", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "\346\270\205\351\231\244\350\267\257\347\272\277", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255\351\237\263\344\271\220", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "\346\222\255\346\224\276\351\237\263\344\271\220", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
