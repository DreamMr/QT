#-------------------------------------------------
#
# Project created by QtCreator 2017-12-29T15:55:04
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
RC_ICONS += tubiao.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Rebirth
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    nine.cpp \
    myitem.cpp \
    myview.cpp \
    mythread.cpp

HEADERS  += mainwindow.h \
    nine.h \
    myitem.h \
    myview.h \
    mythread.h \
    a_star.h \
    heap.h \
    a_node.h

FORMS    += mainwindow.ui \
    nine.ui
