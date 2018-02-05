#ifndef FORM_H
#define FORM_H
#include<QPixmap>
#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    QPixmap *pixmap;
    QString text;
    void setup(QString r,QString t);
    void paintEvent(QPaintEvent *);
private:
    Ui::Form *ui;
};

#endif // FORM_H
