#ifndef HTMLVIEW_H
#define HTMLVIEW_H

#include <QtWebKitWidgets>
#include "webinterface.h"
#include "webview.h"

class HtmlView : public QWidget
{
    Q_OBJECT
public:
    explicit HtmlView(QWidget *parent = 0);
    WebView * webView(){return _view;}
    WebInterface * interface(){return _interface;}
private:
    WebView * _view;
    WebInterface * _interface;
protected:
    void resizeEvent(QResizeEvent *e);
    void changeEvent(QEvent *e);

signals:

public slots:
    void addInterface();
};

#endif // HTMLVIEW_H
