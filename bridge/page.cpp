#include "page.h"

#include <QNetworkRequest>
#include <QtWebKitWidgets>

Page::Page(QWidget *parent) :
    QWebPage(parent)
{
}

bool Page::acceptNavigationRequest(QWebFrame *frame, const QNetworkRequest &request, QWebPage::NavigationType type)
{
    qDebug()<<request.url();
    return true;
}
