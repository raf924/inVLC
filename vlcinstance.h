#ifndef VLCINSTANCE_H
#define VLCINSTANCE_H

#include <vlc/vlc.h>
#include <QList>

typedef QList<libvlc_event_e> EventList;

class VlcInstance
{
public:
    libvlc_instance_t * instance();
    void release();
    static VlcInstance *load();
    EventList mediaEvents(){return _mediaEvents;}
    EventList mediaPlayerEvents(){ return _mediaPlayerEvents;}
    EventList mediaListEvents(){return _mediaListEvents;}
    EventList mediaListPlayerEvents(){return _mediaListPlayerEvents;}
private:
    VlcInstance();
    static VlcInstance * _vlc;
    libvlc_instance_t * _instance;
    EventList _mediaEvents;
    EventList _mediaPlayerEvents;
    EventList _mediaListEvents;
    EventList _mediaListPlayerEvents;
};

#endif // VLC_H
