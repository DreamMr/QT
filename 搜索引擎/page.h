#ifndef PAGE_H
#define PAGE_H
#include<QGraphicsScene>
#include <QWidget>
#include<vector>
#include<string>
#include<algorithm>
#include"url_index.h"
#include"urlitem.h"
using namespace std;
namespace Ui {
class Page;
}

class Page : public QWidget
{
    Q_OBJECT

public:
    explicit Page(QWidget *parent = 0);
    ~Page();
    QGraphicsScene scene;
    void setPage(int page_numer);
    URLITEM *item;
    bool flag;
    vector<SORT_STRUCT>v;
public slots:
    void receivepageurl(QString u);
signals:
    void sendpageurl(QString u);
private slots:
    void on_pushButton_clicked();

private:
    Ui::Page *ui;
    int line;//用于控制文本排版
    int page_count;//记录查找的结果总数
    //int LineNumber(QString info);
    void trans(URLITEM *item);//文本的排版
};

#endif // PAGE_H
