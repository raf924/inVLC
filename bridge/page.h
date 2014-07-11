#ifndef PAGE_H
#define PAGE_H

#include <QWebPage>

class Page : public QWebPage
{
    Q_OBJECT
public:
    explicit Page(QWidget *parent = 0);
protected:
    bool acceptNavigationRequest(QWebFrame *frame, const QNetworkRequest &request, NavigationType type);

signals:

public slots:

};

#endif // PAGE_H
