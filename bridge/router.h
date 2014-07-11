#ifndef ROUTER_H
#define ROUTER_H

#include <QObject>
#include <QVariant>

class Router : public QObject
{
    Q_OBJECT
public:
    explicit Router(QObject *parent = 0);
    void addRoute(const QString & route, QObject *actor, const QString &method);
    QString route(const QString & route);
    void debug();
private:
    QVariantMap _routes;
signals:

public slots:

};

#endif // ROUTER_H
