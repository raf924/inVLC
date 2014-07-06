#ifndef WEBINTERFACE_H
#define WEBINTERFACE_H

#include <QObject>
#include <QVariant>

class WebInterface : public QObject
{
    Q_OBJECT

public:
    explicit WebInterface(QObject *parent = 0);
    void setRestore(bool restore){_restore = restore;}
    bool restore(){return _restore;}
    Q_PROPERTY(bool restore MEMBER _restore READ restore NOTIFY restoreChanged)
private:
    bool _restore;
signals:
    void play();
    void pause();
    void stop();
    void seek(const QVariant &);
    void volume(const QVariant &);
    void restoreChanged(bool);
    void close();

public slots:
    void action(const QMap<QString, QVariant> &actionData);

};

#endif // WEBINTERFACE_H
