#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include "library/playlist.h"
#include "library/library.h"
#include "core/medialistplayer.h"
#include "bridge/htmlview.h"
#include "bridge/webinterface.h"

class Application : public QObject
{
    Q_OBJECT
public:
    explicit Application(QObject *parent = 0);

signals:

public slots:
private:
    HtmlView * _view;
    Player * _player;
    Library * _library;
    QList<Playlist *> _playlists;

};

#endif // APPLICATION_H
