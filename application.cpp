#include "application.h"

Application::Application(QObject *parent) :
    QObject(parent)
{
    QDir inVLCpath(QStandardPaths::writableLocation(QStandardPaths::MusicLocation));
    inVLCpath.mkdir("inVLC");
    _player = new Player;
    _view = new HtmlView;
    _library = new Library;
    foreach (QString playlist, Playlist::playlists()) {
        _playlists.append(new Playlist(playlist));
    }
    _view->webView()->page()->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled,true);
    QWebInspector * inspector = new QWebInspector;
    inspector->setPage(_view->webView()->page());
    inspector->setVisible(true);
    connect(_view->interface(),SIGNAL(seek(const QVariant &)),_player,SLOT(seek(const QVariant &)));
    connect(_player,SIGNAL(lengthChanged(qint64)),_view->interface(),SIGNAL(lengthChanged(qint64)));
    connect(_player,SIGNAL(timeChanged(qint64)),_view->interface(),SIGNAL(timeChanged(qint64)));
    connect(_player,SIGNAL(metaDataParsed(QVariantMap)),_view->interface(),SLOT(setMetaData(QVariantMap)));
    _view->showMaximized();
    _library->add(new Media("D:\\Music\\Music\\CCXL.mp3"));
}
