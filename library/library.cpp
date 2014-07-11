#include "library.h"

#include <QDesktopServices>

Library::Library(QObject *parent) :
    QObject(parent)
{
    _dataBase = QSqlDatabase::addDatabase("QSQLITE");
    _dataBase.setDatabaseName(QStandardPaths::writableLocation(QStandardPaths::MusicLocation)+"/inVLC/library.db");
    if(!_dataBase.open())
        qDebug()<<"Can't open database"<<_dataBase.databaseName();
    _dataBase.exec("create table library (Path TEXT, PRIMARY KEY(Path))");
    qDebug()<<_dataBase.lastError().text();
}

QList<QVariantMap> Library::library()
{
    QList<QVariantMap> list;
    QSqlQuery query;
    query.prepare("SELECT * FROM library");
    query.exec();
    while(query.next()){
        QVariantMap map;
        for(int i = 0;i<query.record().count();i++)
            map.insert(query.record().fieldName(i),query.value(i).toString());
            list.append(map);
    }
    return list;
}

void Library::add(const QList<QVariantMap> &metaData)
{
    foreach (QVariantMap file, metaData) {
        QSqlQuery query;
        query.prepare("INSERT INTO library (Path)  VALUES(:id)");
        query.bindValue(":id",file.value("Path"));
        query.exec();
        foreach (QString field, file.keys()) {
            query.prepare("ALTER TABLE library ADD COLUMN "+field+" TEXT");
            query.exec();
            query.prepare("UPDATE library SET "+field+" = :value WHERE Path = :id");
            query.bindValue(":value",file.value(field));
            query.bindValue(":id",file.value("Path"));
            query.exec();
        }
    }
}

void Library::add(Media *media)
{
    qDebug()<<media->metaData();
    add(QList<QVariantMap>()<<media->metaData());
}

Library::~Library()
{
    _dataBase.close();
}
