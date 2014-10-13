#ifndef LIBRARY_H
#define LIBRARY_H

#include <QObject>
#include <QtSql>

#include <core/media.h>

class Library : public QObject
{
    Q_OBJECT
public:
    explicit Library(QObject *parent = 0);
    Q_INVOKABLE QVariantList library();
    Media *getSong(const int & id);
    void add(const QList<QVariantMap> & metaData);

    void add(Media * media);
    ~Library();
private:
    QSqlDatabase _dataBase;
signals:

public slots:

};

#endif // LIBRARY_H
