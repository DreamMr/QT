#include "search_page.h"
#include "ui_search_page.h"
#include<QUrl>
SEARCH_PAGE::SEARCH_PAGE(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SEARCH_PAGE)
{
    ui->setupUi(this);
    view=new QWebEngineView(this);
    view->show();
}

SEARCH_PAGE::~SEARCH_PAGE()
{
    delete view;
    delete ui;
}
