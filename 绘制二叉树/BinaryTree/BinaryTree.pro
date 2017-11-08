#-------------------------------------------------
#
# Project created by QtCreator 2017-10-18T18:21:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BinaryTree
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    dialog_pre.cpp \
    dialog_premid.cpp \
    mydock.cpp \
    dialog.cpp

HEADERS  += widget.h \
    dialog_pre.h \
    dialog_premid.h \
    mydock.h \
    binarytree.h \
    binarytreenode.h \
    dialog.h \
    queue.h

FORMS    += widget.ui \
    dialog_pre.ui \
    dialog_premid.ui \
    mydock.ui \
    dialog.ui
