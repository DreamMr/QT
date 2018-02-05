#-------------------------------------------------
#
# Project created by QtCreator 2018-01-24T20:57:39
#
#-------------------------------------------------

QT       += core gui
RC_ICONS += tubiao.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = search_engine
TEMPLATE = app
QT += qml quick webview
QT       += core gui webenginewidgets
QT += webenginewidgets
SOURCES += main.cpp\
        mainwindow.cpp \
    page.cpp \
    search_engine.cpp \
    search_page.cpp \
    urlitem.cpp \
    mythread.cpp \
    getline.cpp

HEADERS  += mainwindow.h \
    bttree.h \
    btnode.h \
    search_engine.h \
    page.h \
    url_index.h \
    search_page.h \
    urlitem.h \
    mythread.h \
    getline.h \
    heap.h

FORMS    += mainwindow.ui \
    page.ui \
    search_page.ui
