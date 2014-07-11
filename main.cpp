#include "bridge/htmlview.h"
#include "core/player.h"

#include <QApplication>
#include <QtCore>

#include <iostream>
#include "application.h"

#include "bridge/router.h"

using namespace std;

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);
    //Application * app = new Application;
    Router * router = new Router;
    Router * router2 = new Router;
    router->addRoute("action", router2,"debug");
    router->route("action");
    return a.exec();
}

