#ifndef NETWORKACCESSMANAGER_H
#define NETWORKACCESSMANAGER_H

#include <QNetworkAccessManager>
#include <QNetworkReply>

class NetworkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit NetworkAccessManager(QObject *parent = 0);
protected:
    virtual QNetworkReply * createRequest(Operation op, const QNetworkRequest &request, QIODevice *outgoingData);
signals:

public slots:

};

#endif // NETWORKACCESSMANAGER_H
