#-------------------------------------------------
#
# Project created by QtCreator 2017-12-23T11:35:25
#
#-------------------------------------------------

QT       += core gui
RC_ICONS += tubiao.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JSONedit
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    treewidget.cpp \
    treewidgetitem.cpp \
    search.cpp \
    codeeditor.cpp

HEADERS  += mainwindow.h \
    treewidget.h \
    treewidgetitem.h \
    search.h \
    codeeditor.h

FORMS    += mainwindow.ui \
    search.ui
