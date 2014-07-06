#ifndef PLAYER_H
#define PLAYER_H

#include <vlc/vlc.h>
#include "media.h"
#include <QObject>

class Player : public QObject
{
    Q_OBJECT
    enum MediaStatus{
        EndOfMedia,
        Buffering,

    };
    enum State{
        Playing,
        Paused,
        Stoppped
    };

public:
    explicit Player(QObject *parent = 0);
    void setMedia(Media * media);
    Media  *media();
    qint64 getTime();
    qint64 getLength();
    QMap<libvlc_meta_t, QString> getMetaData();
    void setVideoOutput(QWidget * w);
    ~Player();

public slots:
    void play();
    void pause();
    void stop();
    void seek(const QVariant & msecs);
    void setVolume(const QVariant & volume);

private:
    libvlc_media_player_t *_player;
    libvlc_event_manager_t * _em;
    EventList _events;
    Media * _media;
    static void processEvent(const libvlc_event_t *event, void *ptr);

    void registerEvents();
signals:
    void timeChanged(qint64);
    void mediaStatusChanged(MediaStatus);
    void stateChanged(State);
    void lengthChanged(qint64);
    void metaDataChanged(QMap<libvlc_meta_t, QString>);

};

#endif // PLAYER_H
