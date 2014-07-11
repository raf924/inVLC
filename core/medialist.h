#ifndef MEDIALIST_H
#define MEDIALIST_H

#include <QObject>
#include <vlc/vlc.h>
#include "media.h"
#include "vlcinstance.h"

class MediaList : public QObject
{
    Q_OBJECT
public:
    explicit MediaList(QObject *parent = 0);
    libvlc_media_list_t * getMediaList(){return _mediaList;}
    void insertMedia(Media *media, const int & index);
    void addMedia(Media *media);
    void removeMedia(int index);
    Media  *at(int index);
    int count(){return _list.count();}
    ~MediaList();
signals:
    void willDeleteItem(libvlc_media_t *, int);
    void itemDeleted(libvlc_media_t *, int);
    void willAddItem(libvlc_media_t *, int);
    void itemAdded(libvlc_media_t *, int);
public slots:
private:
    static void processEvent(const libvlc_event_t * event, void *data);
    EventList _events;
    QList<Media *> _list;
    libvlc_media_list_t * _mediaList;
    void registerEvents();

};

#endif // MEDIALIST_H
