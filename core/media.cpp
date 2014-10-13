#include "media.h"

#include <QtCore>

Media::Media(QObject *parent):
    QObject(parent)
{
    _media = NULL;
}

/**
 * @brief Media::Media Constructs a Media Object from a URL (example : "file:///path/to/file.mp3")
 * @param location : The URL encoded path of the file
 */

Media::Media(const QUrl &location)
{
    _media = libvlc_media_new_location(VlcInstance::load()->instance(),location.toString().toUtf8().data());
    registerEvents();
    qDebug()<<"Media created from url";
}

Media::Media(const QString &path)
{
    qDebug()<<"Creating media from path"<<path.toUtf8().data();
    _media = libvlc_media_new_path(VlcInstance::load()->instance(),path.toUtf8().data());
    registerEvents();
    qDebug()<<"Media created from path";
}

QVariantMap Media::metaData()
{
    QVariantMap metaData;
    const QMetaObject & mo = Media::staticMetaObject;
    QMetaEnum metaEnum = mo.enumerator(mo.indexOfEnumerator("MetaData"));
    for(int i = 0;i<= metaEnum.keyCount();i++){
        if(!QString(metaEnum.valueToKey(i)).isEmpty()){
            metaData.insert(tr(metaEnum.valueToKey(i)),libvlc_media_get_meta(_media,static_cast<libvlc_meta_t>(i)));
        }
    }
    metaData.insert("Path",libvlc_media_get_mrl(_media));
    QTime t(0,0,0);
    t = t.addMSecs(libvlc_media_get_duration(_media));
    metaData.insert("Duration",t.toString((t.hour()>0?"hh:":"")+QString("mm:ss")));
    return metaData;
}

QString Media::getMetaData(Media::MetaData tag)
{
    return libvlc_media_get_meta(_media,static_cast<libvlc_meta_t>(tag));
}

Media::~Media()
{
    foreach (const libvlc_event_e & event, VlcInstance::load()->mediaEvents()) {
        libvlc_event_detach(libvlc_media_event_manager(_media),event,processEvent,this);
    }
    libvlc_media_release(_media);
}

void Media::registerEvents()
{
    foreach (const libvlc_event_e & event, VlcInstance::load()->mediaEvents()) {
        libvlc_event_attach(libvlc_media_event_manager(_media),event,processEvent,this);
    }
    libvlc_media_parse(_media);
    for(int i = 0; i< 20;i++){
        //qDebug()<<libvlc_media_get_meta(_media,static_cast<libvlc_meta_t>(i));
    }
}

void Media::processEvent(const libvlc_event_t * e, void *data)
{
    Media * media = (Media *)data;
    switch (e->type) {
    case libvlc_MediaMetaChanged:
        emit media->metaDataParsed(media->metaData());
        break;
    case libvlc_MediaDurationChanged:
        emit media->durationChanged(e->u.media_duration_changed.new_duration);
        break;
    case libvlc_MediaSubItemAdded:
        break;
    case libvlc_MediaFreed:
        break;
    case libvlc_MediaStateChanged:
        break;
    case libvlc_MediaSubItemTreeAdded:
        break;
    case libvlc_MediaParsedChanged:
        emit media->metaDataParsed(media->metaData());
        break;
    }
}
