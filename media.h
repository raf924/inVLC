#ifndef MEDIA_H
#define MEDIA_H

#include <vlc/vlc.h>
#include <QUrl>
#include "vlcinstance.h"

class Media
{
public:
    explicit Media();
    Media(const QUrl & location);
    Media(const QString & path);
    libvlc_media_t * getMedia(){return _media;}
    ~Media();
private:
    EventList _events;
    libvlc_media_t *_media;
    void registerEvents();
    static void processEvent(const libvlc_event_t *e, void * data);

};

#endif // MEDIA_H
