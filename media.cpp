#include "media.h"

#include <QtCore>

Media::Media()
{
    _media = NULL;
}

Media::Media(const QUrl &location)
{
    _media = libvlc_media_new_location(VlcInstance::load()->instance(),location.toString().toUtf8().data());
}

Media::Media(const QString &path)
{
    _media = libvlc_media_new_path(VlcInstance::load()->instance(),path.toUtf8().data());
}

Media::~Media()
{
    foreach (const libvlc_event_e & event, _events) {
        libvlc_event_detach(libvlc_media_event_manager(_media),event,processEvent,this);
    }
    libvlc_media_release(_media);
}

void Media::registerEvents()
{
    libvlc_event_manager_t * em = libvlc_media_event_manager(_media);
    foreach (const libvlc_event_e & event, _events) {
        libvlc_event_attach(em,event,processEvent,this);
    }
}

void Media::processEvent(const libvlc_event_t * e, void *data)
{

}
