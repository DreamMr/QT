#-------------------------------------------------
#
# Project created by QtCreator 2017-11-27T15:54:44
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
RC_ICONS += xiaohui.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = daohang
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qview.cpp \
    myitem.cpp \
    form.cpp

HEADERS  += mainwindow.h \
    qview.h \
    vector.h \
    myitem.h \
    form.h

FORMS    += mainwindow.ui \
    form.ui
