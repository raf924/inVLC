#include "player.h"
#include "media.h"

#include <QFileDialog>
#include <QDebug>
#include <QtQml>

void Player::processEvent(const libvlc_event_t *event, void *ptr)
{
    Player * self = reinterpret_cast<Player *>(ptr);
    switch(event->type){
    case libvlc_MediaPlayerTimeChanged:
        emit self->timeChanged(self->getTime());
        break;
    case libvlc_MediaPlayerOpening:
        qDebug()<<"Opening Media";
        break;
    case libvlc_MediaPlayerLengthChanged:
        emit self->lengthChanged(self->getLength());
        break;
    case libvlc_MediaPlayerMediaChanged:
        qDebug()<<"Meta Data Changed";
        emit self->metaDataChanged(self->getMetaData());
        break;
    }
}

Player::Player(QObject *parent) :
    QObject(parent)
{
    _player = libvlc_media_player_new(VlcInstance::load()->instance());
    _em = libvlc_media_player_event_manager(_player);
    registerEvents();
}

void Player::setMedia(Media *media)
{
    _media = media;
    libvlc_media_parse(_media->getMedia());
    libvlc_media_player_set_media(_player,media->getMedia());
}

Media *Player::media()
{
    return _media;
}

qint64 Player::getTime()
{
    return libvlc_media_player_get_time(_player);
}

qint64 Player::getLength()
{
    return libvlc_media_player_get_length(_player);
}

QMap<libvlc_meta_t, QString> Player::getMetaData()
{
    QMap<libvlc_meta_t, QString> meta;
    QList<libvlc_meta_t> tags;
    tags << libvlc_meta_Title
            <<libvlc_meta_Artist
            <<libvlc_meta_Genre
            <<libvlc_meta_Copyright
            <<libvlc_meta_Album
            <<libvlc_meta_TrackNumber
            <<libvlc_meta_Description
            <<libvlc_meta_Rating
            <<libvlc_meta_Date
            <<libvlc_meta_Setting
            <<libvlc_meta_URL
            <<libvlc_meta_Language
            <<libvlc_meta_NowPlaying
            <<libvlc_meta_Publisher
            <<libvlc_meta_EncodedBy
            <<libvlc_meta_ArtworkURL
            <<libvlc_meta_TrackID;
    foreach(libvlc_meta_t tag, tags)
    {
        meta.insert(tag,libvlc_media_get_meta(_media->getMedia(),tag));
    }
    return meta;
}

void Player::setVideoOutput(QWidget *w)
{
    libvlc_media_player_set_hwnd(_player,(HWND)w->winId());
}

Player::~Player()
{
    foreach(const libvlc_event_e & event, _events)
    {
        libvlc_event_detach( _em, event,processEvent, this );
    }
    stop();
    libvlc_media_player_release(_player);
    VlcInstance::load()->release();
}

void Player::play()
{
    libvlc_media_player_play(_player);
}

void Player::pause()
{
    libvlc_media_player_pause(_player);
}

void Player::stop()
{
    libvlc_media_player_stop(_player);
}

void Player::seek(const QVariant &msecs)
{
    libvlc_media_player_set_time(_player,msecs.toLongLong());
}

void Player::setVolume(const QVariant &volume)
{
    libvlc_audio_set_volume(_player,volume.toInt());
}

void Player::registerEvents()
{
    foreach(const libvlc_event_e & event, _events)
    {
        libvlc_event_attach( _em, event,processEvent, this );
    }
}


