#ifndef SEARCH_PAGE_H
#define SEARCH_PAGE_H

#include <QWidget>
#include<QWebEngineView>
//yongyu xianshiwangye
namespace Ui {
class SEARCH_PAGE;
}

class SEARCH_PAGE : public QWidget
{
    Q_OBJECT

public:
    explicit SEARCH_PAGE(QWidget *parent = 0);
    ~SEARCH_PAGE();
     QWebEngineView *view;//显示网页

private:
    Ui::SEARCH_PAGE *ui;
};

#endif // SEARCH_PAGE_H
