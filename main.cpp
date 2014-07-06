#include "htmlview.h"
#include "player.h"

#include <QApplication>
#include <QtCore>

#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);
    HtmlView hv;
    hv.webView()->page()->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    QWebInspector inspector;
    inspector.setPage(hv.webView()->page());
    inspector.setVisible(true);
    hv.showMaximized();
    Player p;
    hv.setPlayer(&p);
    p.setMedia(new Media("CCXL.mp3"));
    p.play();
    return a.exec();
}

