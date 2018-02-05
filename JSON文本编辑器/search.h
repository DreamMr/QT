#ifndef SEARCH_H
#define SEARCH_H

#include <QWidget>

namespace Ui {
class Search;
}

class Search : public QWidget
{
    Q_OBJECT

public:
    explicit Search(QWidget *parent = 0);
    ~Search();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

signals:
    bool Find(int mode,QString _string);
private:
    Ui::Search *ui;
};

#endif // SEARCH_H
