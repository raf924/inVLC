#include "playlist.h"

#include <QSqlQuery>
#include <QStandardPaths>

Playlist::Playlist(const QString &name, QObject *parent) :
    QObject(parent),
    _name(name)
{
    _dataBase = QSqlDatabase::addDatabase("QSQLITE",name);
    _dataBase.setDatabaseName(QStandardPaths::writableLocation(QStandardPaths::MusicLocation)+"/inVLC/playlists.db");
    _dataBase.open();
}

QVariantMap Playlist::playlist()
{
    QVariantMap map;
    QSqlQuery query;
    query.prepare("SELECT * FROM :playlist");
    query.bindValue(":playlist",_name);
    query.exec();
    while(query.next()){
        map.insert(query.record().fieldName(query.at()),query.value(query.at()));
    }
    return map;
}

QStringList Playlist::playlists()
{
    QSqlDatabase dataBase = QSqlDatabase::addDatabase("QSQLITE","playlists");
    dataBase.setDatabaseName(QStandardPaths::writableLocation(QStandardPaths::MusicLocation)+"/inVLC/playlists.db");
    dataBase.open();
    QStringList list = dataBase.tables();
    dataBase.close();
    return list;
}

Playlist::~Playlist()
{
    _dataBase.close();
}

Playlist * Playlist::createPlaylist(const QString &name)
{
    QSqlDatabase dataBase = QSqlDatabase::addDatabase("QSQLITE","create");
    dataBase.setDatabaseName(QStandardPaths::writableLocation(QStandardPaths::MusicLocation)+"/inVLC/playlists.db");
    dataBase.open();
    QSqlQuery query;
    query.prepare("create table :name");
    query.bindValue(":name",name);
    query.exec();
    dataBase.close();
    return new Playlist(name);
}
