#include "router.h"
#include <QDebug>
#include <QMetaObject>
#include <QMetaMethod>

Router::Router(QObject *parent) :
    QObject(parent)
{
}

void Router::addRoute(const QString &route, QObject * actor, const QString &method)
{
    QVariantMap action;
    action.insert("object",QVariant(QMetaType::QObjectStar,actor));
    action.insert("method",method);
    _routes.insert(route,action);
}

QString Router::route(const QString &route)
{
    QObject * actor = qvariant_cast<QObject*>(_routes.value(route).toMap().value("object"));
    actor->metaObject()->invokeMethod(actor,_routes.value(route).toMap().value("method").toString().toUtf8());
}

void Router::debug()
{
    qDebug()<<"_routes";
}
