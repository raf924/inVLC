#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QGraphicsWebView>

class WebView : public QGraphicsWebView
{
public:
    WebView(QGraphicsItem * item = 0);
protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *e);
};

#endif // WEBVIEW_H
