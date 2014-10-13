#include "webview.h"
#include <QDebug>
#include "networkaccessmanager.h"
#include "page.h"


WebView::WebView(QGraphicsItem *item):
    QGraphicsWebView(item)
{
    this->setPage(new Page());
    this->page()->setNetworkAccessManager(new NetworkAccessManager());
    this->page()->setForwardUnsupportedContent(true);
}

void WebView::contextMenuEvent(QGraphicsSceneContextMenuEvent *e)
{

}
