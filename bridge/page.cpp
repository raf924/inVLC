#include "page.h"

#include <QNetworkRequest>
#include <QtWebKitWidgets>

Page::Page(QWidget *parent) :
    QWebPage(parent)
{
}

bool Page::acceptNavigationRequest(QWebFrame *frame, const QNetworkRequest &request, QWebPage::NavigationType type)
{
    /*qDebug()<<frame->toHtml();
    if(request.url().scheme()=="invlc"){
        qDebug()<<request.url().host();
    }*/
    return true;
}
