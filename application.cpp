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
    connect(_view->interface(),SIGNAL(getSongList()),this,SLOT(sendSongList()));
    connect(_view->interface(),SIGNAL(addFile()),this,SLOT(addFile()));
    connect(_view->interface(),SIGNAL(addFolder()),this,SLOT(addFolder()));
    connect(_view->interface(),SIGNAL(openFile()),this,SLOT(openFile()));
    connect(_view->interface(),SIGNAL(play(int)),this,SLOT(play(int)));
    connect(_view->interface(),SIGNAL(play()),_player,SLOT(play()));
    connect(_view->interface(),SIGNAL(pause()),_player,SLOT(pause()));
    connect(_view->interface(),SIGNAL(stop()),_player,SLOT(stop()));
    connect(_player,SIGNAL(stateChanged(State)),_view->interface(),SIGNAL(paused(State)));
    _view->showMaximized();
}

void Application::sendSongList()
{
    emit _view->interface()->songListUpdated(_library->library());
}

void Application::addFile()
{
    QString file = QFileDialog::getOpenFileName(_view,tr("Add a file"));
    _library->add(new Media(QUrl::fromLocalFile(file)));
    sendSongList();
}

void Application::openFile()
{

}

void Application::addFolder()
{

}

void Application::play(const int &id)
{
    _player->setMedia(_library->getSong(id));
    _player->play();
}
