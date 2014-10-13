#include "player.h"
#include "media.h"

#include <QDebug>
#include <QtWidgets>
#include <windows.h>

void Player::processEvent(const libvlc_event_t *event, void *ptr)
{
    Player * self = reinterpret_cast<Player *>(ptr);
    switch(event->type){
    case libvlc_MediaPlayerTimeChanged:
        emit self->timeChanged(self->getTime());
        break;
    case libvlc_MediaPlayerOpening:
        break;
    case libvlc_MediaPlayerLengthChanged:
        emit self->lengthChanged(self->getLength());
        break;
    case libvlc_MediaPlayerMediaChanged:
        break;
    case libvlc_MediaPlayerPaused:
        qDebug()<<"Paused";
        emit self->stateChanged(Paused);
        break;
    case libvlc_MediaPlayerPlaying:
        qDebug()<<"Playing";
        emit self->stateChanged(Playing);
        break;
    case libvlc_MediaPlayerStopped:
        emit self->stateChanged(Stopped);
        break;
    }
}

Player::Player(QObject *parent) :
    QObject(parent),
    _media(0)
{
    _mediaPlayer = libvlc_media_player_new(VlcInstance::load()->instance());
    _em = libvlc_media_player_event_manager(_mediaPlayer);
    registerEvents();
}

void Player::setMedia(Media *media)
{
    _media = media;
    libvlc_media_player_set_media(_mediaPlayer,media->getMedia());
    connect(_media,SIGNAL(metaDataParsed(QVariantMap)),this,SIGNAL(metaDataParsed(QVariantMap)));
}

Media *Player::media()
{
    return _media;
}

qint64 Player::getTime()
{
    return libvlc_media_player_get_time(_mediaPlayer);
}

qint64 Player::getLength()
{
    return libvlc_media_player_get_length(_mediaPlayer);
}

void Player::setVideoOutput(QWidget *w)
{
    libvlc_media_player_set_hwnd(_mediaPlayer,(HWND)w->winId());
}

Player::~Player()
{
    foreach(const libvlc_event_e & event, VlcInstance::load()->mediaPlayerEvents())
    {
        libvlc_event_detach( _em, event,processEvent, this );
    }
    stop();
    libvlc_media_player_release(_mediaPlayer);
    VlcInstance::load()->release();
}

void Player::play()
{
    libvlc_media_player_play(_mediaPlayer);
}

void Player::pause()
{
    libvlc_media_player_pause(_mediaPlayer);
}

void Player::stop()
{
    libvlc_media_player_stop(_mediaPlayer);
}

void Player::seek(const QVariant &msecs)
{
    libvlc_media_player_set_time(_mediaPlayer,msecs.toLongLong());
}

void Player::setVolume(const QVariant &volume)
{
    libvlc_audio_set_volume(_mediaPlayer,volume.toInt());
}

void Player::registerEvents()
{
    foreach(const libvlc_event_e & event, VlcInstance::load()->mediaPlayerEvents())
    {
        libvlc_event_attach( _em, event,processEvent, this );
    }
}


