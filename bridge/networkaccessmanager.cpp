#include "networkaccessmanager.h"
#include "networkreply.h"

NetworkAccessManager::NetworkAccessManager(QObject *parent) :
    QNetworkAccessManager(parent)
{
}

QNetworkReply *NetworkAccessManager::createRequest(QNetworkAccessManager::Operation op, const QNetworkRequest &request, QIODevice *outgoingData)
{
    if(request.url().scheme()=="inVLC"){
        qDebug()<<request.url().path()<<outgoingData->readAll();
        NetworkReply * reply = new NetworkReply(QNetworkAccessManager::createRequest(op,request));
        reply->open(QIODevice::ReadWrite);
        reply->setStatus(400,"OK");
        return reply;
    }
    return QNetworkAccessManager::createRequest(op,request,outgoingData);

}
