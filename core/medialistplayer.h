#ifndef MEDIALISTPLAYER_H
#define MEDIALISTPLAYER_H

#include <QObject>
#include <vlc/vlc.h>
#include "medialist.h"
#include "player.h"

class MediaListPlayer : public QObject
{
    Q_OBJECT
public:
    explicit MediaListPlayer(Player * p, QObject *parent = 0);
    void setMediaList(MediaList * list);
    ~MediaListPlayer();
signals:

public slots:
private:
    EventList _events;
    static void processEvent(const libvlc_event_t * event, void *data);
    void registerEvents();
    libvlc_media_list_player_t * _mediaListPlayer;
    MediaList * _list;

};

#endif // MEDIALISTPLAYER_H
