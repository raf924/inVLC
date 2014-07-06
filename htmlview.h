#ifndef HTMLVIEW_H
#define HTMLVIEW_H

#include <QtWebKitWidgets>
#include "player.h"
#include "webinterface.h"
#include "webview.h"

class HtmlView : public QWidget
{
    Q_OBJECT
public:
    explicit HtmlView(QWidget *parent = 0);
    WebView * webView(){return _view;}
    void setPlayer(Player * player);
private:
    WebView * _view;
    WebInterface * _interface;
    Player * _player;
protected:
    void resizeEvent(QResizeEvent *e);
    void changeEvent(QEvent *e);

signals:

public slots:
    void addInterface();
    void updateMetaData(const QMap<libvlc_meta_t,QString> & metaData);

};

#endif // HTMLVIEW_H
