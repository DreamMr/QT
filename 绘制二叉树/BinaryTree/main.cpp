#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setFixedSize(382,200);
    w.setWindowFlags(Qt::WindowCloseButtonHint);
    w.setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    w.show();

    return a.exec();
}
