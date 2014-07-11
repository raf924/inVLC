#ifndef MEDIA_H
#define MEDIA_H

#include <vlc/vlc.h>
#include <QUrl>
#include "vlcinstance.h"
#include <QObject>

class Media : public QObject
{
    Q_OBJECT

    Q_ENUMS(MetaData)

public:
    explicit Media(QObject * parent = 0);
    Media(const QUrl & location);
    Media(const QString & path);
    libvlc_media_t * getMedia(){return _media;}
    QVariantMap metaData();
    enum MetaData{
        Title,
        Artist,
        Genre,
        Copyright,
        Album,
        TrackNumber,
        Description,
        Rating,
        Date,
        Setting,
        Url,
        Language,
        NowPlaying,
        Publisher,
        EncodedBy,
        ArtworkUrl,
        TrackId,
    };
    QString getMetaData(MetaData tag);
    ~Media();
private:
    EventList _events;
    libvlc_media_t *_media;
    void registerEvents();
    static void processEvent(const libvlc_event_t *e, void * data);
signals:
    void metaDataParsed(const QVariantMap &);
    void durationChanged(const qint64 &);

};

#endif // MEDIA_H
