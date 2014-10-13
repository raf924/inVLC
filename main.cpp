#include <QApplication>
#include <QtCore>

#include <iostream>
#include "application.h"

using namespace std;

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<int>("State");
    Application * app = new Application;
    return a.exec();
}

