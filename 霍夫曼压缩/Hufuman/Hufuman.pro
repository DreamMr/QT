#-------------------------------------------------
#
# Project created by QtCreator 2017-10-28T08:52:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Hufuman
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    compression_nuw.cpp

HEADERS  += mainwindow.h \
    binarytreenode.h \
    huffmantree.h \
    heap.h \
    compression_nuw.h

FORMS    += mainwindow.ui
