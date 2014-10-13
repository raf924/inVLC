#ifndef WEBINTERFACE_H
#define WEBINTERFACE_H

#include <QObject>
#include <QVariant>
#include <QDebug>
#include "core/player.h"

class WebInterface : public QObject
{
    Q_OBJECT

public:
    explicit WebInterface(QObject *parent = 0);
    void setRestore(bool restore){_restore = restore;}
    bool getRestore(){return _restore;}
    Q_INVOKABLE QVariantMap metaData(){return _nowPlaying;}
    Q_PROPERTY(bool restore MEMBER _restore READ getRestore NOTIFY restoreChanged)
    Q_PROPERTY(QVariantMap nowPlaying MEMBER _nowPlaying READ metaData NOTIFY metaDataChanged)
private:
    bool _restore;
    QVariantMap _nowPlaying;
signals:
    void play(const int &);
    void play();
    void pause();
    void paused(State);
    void stop();
    void seek(const QVariant &);
    void volume(const QVariant &);
    void restoreChanged(bool);
    void close();
    void timeChanged(const qint64 &);
    void lengthChanged(const qint64 &);
    void metaDataChanged(const QVariantMap &);
    void songListUpdated(const QVariantList &);
    void getSongList();
    void hide();
    void restore();
    void expand();
    void addFile();
    void openFile();
    void addFolder();

public slots:
    void action(const QVariantMap &actionData);
    void setMetaData(const QVariantMap & metaData){_nowPlaying = metaData;}
};

#endif // WEBINTERFACE_H
