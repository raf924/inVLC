#ifndef WEBINTERFACE_H
#define WEBINTERFACE_H

#include <QObject>
#include <QVariant>

class WebInterface : public QObject
{
    Q_OBJECT

public:
    explicit WebInterface(QObject *parent = 0);
    void setRestore(bool restore){_restore = restore;}
    bool restore(){return _restore;}
    QVariantMap metaData(){return _nowPlaying;}
    Q_PROPERTY(bool restore MEMBER _restore READ restore NOTIFY restoreChanged)
    Q_PROPERTY(QVariantMap nowPlaying MEMBER _nowPlaying READ metaData NOTIFY metaDataChanged)
private:
    bool _restore;
    QVariantMap _nowPlaying;
signals:
    void play();
    void pause();
    void stop();
    void seek(const QVariant &);
    void volume(const QVariant &);
    void restoreChanged(bool);
    void close();
    void timeChanged(const qint64 &);
    void lengthChanged(const qint64 &);
    void metaDataChanged(const QVariantMap &);

public slots:
    void action(const QVariantMap &actionData);
    void setMetaData(const QVariantMap & metaData){_nowPlaying = metaData;}
};

#endif // WEBINTERFACE_H
