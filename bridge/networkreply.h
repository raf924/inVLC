#ifndef NETWORKREPLY_H
#define NETWORKREPLY_H

#include <QNetworkReply>

class NetworkReply : public QNetworkReply
{
    Q_OBJECT
public:
    explicit NetworkReply(QNetworkReply * reply, QObject *parent = 0);
    void setStatus(int code, QString statusText);
    void abort();
    bool isSequential(){return true;}
    qint64 bytesAvailable();
    ~NetworkReply();
    void setContent(const QString & content, const QString &contentType = QString());
private:
    struct NetworkReplyPrivate *d;
protected:
    qint64 readData(char *data, qint64 maxlen);

signals:

public slots:

};

#endif // NETWORKREPLY_H
