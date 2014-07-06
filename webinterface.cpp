#include "webinterface.h"
#include <QDebug>


WebInterface::WebInterface(QObject *parent) :
    QObject(parent),
    _restore(true)
{
}

void WebInterface::action(const QMap<QString,QVariant> &actionData)
{
    qDebug()<<actionData.value("action")<<actionData.value("data");
    QString action = actionData.value("action").toString();
    QVariant data = actionData.value("data");
    if(data.isNull()){
        this->metaObject()->invokeMethod(this,action.toUtf8().data());
    }else{
        this->metaObject()->invokeMethod(this,action.toUtf8().data(),QGenericArgument("QVariant",data.data()));
    }
}
