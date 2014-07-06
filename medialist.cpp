#include "medialist.h"

MediaList::MediaList(QObject *parent) :
    QObject(parent)
{
    _mediaList = libvlc_media_list_new(VlcInstance::load()->instance());
    _events = VlcInstance::load()->mediaListEvents();
}

void MediaList::insertMedia(Media *media, const int &index)
{
    libvlc_media_list_lock(_mediaList);
    libvlc_media_list_insert_media(_mediaList,media->getMedia(),index);
    _list.insert(index,media);
    libvlc_media_list_unlock(_mediaList);
}

void MediaList::addMedia(Media *media)
{
    libvlc_media_list_lock(_mediaList);
    libvlc_media_list_add_media(_mediaList,media->getMedia());
    libvlc_media_list_unlock(_mediaList);
}

void MediaList::removeMedia(int index)
{
    libvlc_media_list_lock(_mediaList);
    libvlc_media_list_remove_index(_mediaList,index);
    delete _list[index];
    _list.removeAt(index);
    libvlc_media_list_unlock(_mediaList);
}

Media *MediaList::at(int index)
{
    return _list.at(index);
}

MediaList::~MediaList()
{
    foreach (Media * media, _list) {
        delete media;
    }
    foreach (const libvlc_event_e & event, _events) {
        libvlc_event_detach(libvlc_media_list_event_manager(_mediaList),event,processEvent,this);
    }
    libvlc_media_list_release(_mediaList);
}

void MediaList::processEvent(const libvlc_event_t *event, void *data)
{
    MediaList * list = (MediaList*)data;
    switch(event->type){
    case libvlc_MediaListItemAdded:
        emit list->itemAdded(event->u.media_list_item_added.item,event->u.media_list_item_added.index);
        break;
    case libvlc_MediaListItemDeleted:
        emit list->itemDeleted(event->u.media_list_item_deleted.item,event->u.media_list_item_deleted.index);
        break;
    case libvlc_MediaListWillAddItem:
        emit list->willAddItem(event->u.media_list_will_add_item.item,event->u.media_list_will_add_item.index);
        break;
    case libvlc_MediaListWillDeleteItem:
        emit list->willDeleteItem(event->u.media_list_will_delete_item.item,event->u.media_list_will_delete_item.index);
        break;
    }
}

void MediaList::registerEvents()
{
    foreach (const libvlc_event_e & event, _events) {
        libvlc_event_attach(libvlc_media_list_event_manager(_mediaList),event,processEvent,this);
    }
}
