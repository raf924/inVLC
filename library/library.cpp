#include "library.h"

#include <QDesktopServices>

Library::Library(QObject *parent) :
    QObject(parent)
{
    _dataBase = QSqlDatabase::addDatabase("QSQLITE");
    _dataBase.setDatabaseName(QStandardPaths::writableLocation(QStandardPaths::MusicLocation)+"/inVLC/library.db");
    if(!_dataBase.open())
        qDebug()<<"Can't open database"<<_dataBase.databaseName();
    if(!_dataBase.tables().contains("library")){
        _dataBase.exec("CREATE TABLE `library` (`Path` TEXT NOT NULL UNIQUE, `Album` TEXT, `Artist`	TEXT, `ArtworkUrl` TEXT, `Copyright` TEXT, `Date` TEXT, `Description` TEXT, `Duration` TEXT, `EncodedBy` TEXT, `Genre` TEXT, `Language`	TEXT, `NowPlaying` TEXT, `Publisher` TEXT, `Rating`	TEXT, `Setting`	TEXT, `Title` TEXT, `TrackId` TEXT, `TrackNumber` TEXT, `Url` TEXT, `Id` INTEGER PRIMARY KEY AUTOINCREMENT);");
    }
    qDebug()<<_dataBase.lastError().text();
}

QVariantList Library::library()
{
    qDebug()<<"Library content requested";
    QVariantList list;
    QSqlQuery query;
    query.prepare("SELECT * FROM library");
    query.exec();
    while(query.next()){
        QVariantMap map;
        for(int i = 0;i<query.record().count();i++)
            map.insert(query.record().fieldName(i),query.value(i).toString());
        list.append(QVariant(map));
    }
    return list;
}

Media *Library::getSong(const int &id)
{
    QSqlQuery query;
    query.prepare("SELECT Path FROM library WHERE Id = :id");
    query.bindValue(":id",id);
    query.exec();
    query.next();
    return new Media(QUrl(query.value("Path").toString()));
}

void Library::add(const QList<QVariantMap> &metaData)
{
    foreach (QVariantMap file, metaData) {
        QSqlQuery query;
        query.prepare("INSERT INTO library (Path)  VALUES(:path)");
        query.bindValue(":path",file.value("Path"));
        query.exec();
        foreach (QString field, file.keys()) {
            query.prepare("UPDATE library SET "+field+" = :value WHERE Path = :id");
            query.bindValue(":value",file.value(field));
            query.bindValue(":id",file.value("Path"));
            query.exec();
        }
    }
}

void Library::add(Media *media)
{
    add(QList<QVariantMap>()<<media->metaData());
}

Library::~Library()
{
    _dataBase.close();
}
