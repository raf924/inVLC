#include "webview.h"
#include <QDebug>
#include <QtMultimediaWidgets>
#include "networkaccessmanager.h"
#include "page.h"


WebView::WebView(QGraphicsItem *item):
    QGraphicsWebView(item)
{
    this->setPage(new Page());
    this->page()->setNetworkAccessManager(new NetworkAccessManager());
}

void WebView::contextMenuEvent(QGraphicsSceneContextMenuEvent *e)
{

}
