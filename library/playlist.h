#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QtSql>

class Playlist : public QObject
{
    Q_OBJECT
public:
    explicit Playlist(const QString & name,QObject *parent = 0);
    QVariantMap playlist();
    static Playlist * createPlaylist(const QString & name);
    QString name(){return _name;}
    static QStringList playlists();
    ~Playlist();
private:
    QString _name;
    QSqlDatabase _dataBase;
signals:

public slots:

};

#endif // PLAYLIST_H
