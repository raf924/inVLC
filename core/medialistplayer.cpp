#include "medialistplayer.h"
#include <QDebug>


MediaListPlayer::MediaListPlayer(Player *p, QObject *parent) :
    QObject(parent)
{
    _mediaListPlayer = libvlc_media_list_player_new(VlcInstance::load()->instance());
    libvlc_media_list_player_set_media_player(_mediaListPlayer,p->getPlayer());
    _events = VlcInstance::load()->mediaListPlayerEvents();
}

void MediaListPlayer::setMediaList(MediaList *list)
{
    _list = list;
    libvlc_media_list_player_set_media_list(_mediaListPlayer,_list->getMediaList());
}

MediaListPlayer::~MediaListPlayer()
{
    foreach (const libvlc_event_e & event, _events) {
        libvlc_event_detach(libvlc_media_list_player_event_manager(_mediaListPlayer),event,processEvent,this);
    }
    libvlc_media_list_player_release(_mediaListPlayer);
}

void MediaListPlayer::processEvent(const libvlc_event_t *event, void *data)
{
    MediaListPlayer *self = (MediaListPlayer *)data;
    qDebug()<<libvlc_event_type_name(event->type);
    switch(event->type){
    case libvlc_MediaListPlayerNextItemSet:
        break;
    case libvlc_MediaListPlayerPlayed:
        break;
    case libvlc_MediaListPlayerStopped:
        break;
    }
}

void MediaListPlayer::registerEvents()
{
    foreach (const libvlc_event_e  & event, _events) {
        libvlc_event_attach(libvlc_media_list_player_event_manager(_mediaListPlayer),event,processEvent,this);
    }
}
