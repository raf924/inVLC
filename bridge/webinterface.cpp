#include "webinterface.h"
#include <QDebug>
#include <core/media.h>


WebInterface::WebInterface(QObject *parent) :
    QObject(parent),
    _restore(true)
{
}

void WebInterface::action(const QVariantMap &actionData)
{
    qDebug()<<actionData.value("action").toString();
    QString action = actionData.value("action").toString();
    QVariant data = actionData.value("data");
    qDebug()<<"Traitement action";
    if(data.isNull()){
        this->metaObject()->invokeMethod(this,action.toUtf8().data());
    }else{
        this->metaObject()->invokeMethod(this,action.toUtf8().data(),QGenericArgument("QVariant",data.data()));
    }
}
