#include "networkreply.h"

#include <QTimer>

struct NetworkReplyPrivate
{
    QByteArray content;
    qint64 offset;
};

NetworkReply::NetworkReply(QNetworkReply *reply, QObject *parent) :
    QNetworkReply(parent)
{
    open(QIODevice::ReadWrite);
    write(reply->readAll());
    close();
    d = new NetworkReplyPrivate;
}

void NetworkReply::setStatus(int code, QString statusText)
{
    setAttribute( QNetworkRequest::HttpStatusCodeAttribute, code );
    if ( statusText.isNull() )
        return;

    setAttribute( QNetworkRequest::HttpReasonPhraseAttribute, statusText );
}

void NetworkReply::abort()
{

}

qint64 NetworkReply::bytesAvailable()
{
    return d->content.size() - d->offset + QIODevice::bytesAvailable();
}

NetworkReply::~NetworkReply()
{
    delete d;
}

void NetworkReply::setContent(const QString &content, const QString &contentType)
{

    setHeader(QNetworkRequest::ContentTypeHeader,contentType);

    d->content = content.toLocal8Bit();
    d->offset = 0;

    open(ReadOnly | Unbuffered);
    setHeader(QNetworkRequest::ContentLengthHeader, QVariant(content.toLocal8Bit().size()));

    QTimer::singleShot( 0, this, SIGNAL(readyRead()) );
    QTimer::singleShot( 0, this, SIGNAL(finished()) );
}

qint64 NetworkReply::readData(char *data, qint64 maxlen)
{
    if (d->offset >= d->content.size())
        return -1;

    qint64 number = qMin(maxlen, d->content.size() - d->offset);
    memcpy(data, d->content.constData() + d->offset, number);
    d->offset += number;

    return number;
}
