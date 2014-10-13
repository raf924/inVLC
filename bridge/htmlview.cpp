#include "htmlview.h"

HtmlView::HtmlView(QWidget *parent) :
    QWidget(parent)
{
    _interface = new WebInterface;
    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::LinksIncludedInFocusChain, false);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::LocalStorageEnabled, true);
    this->setWindowFlags(Qt::FramelessWindowHint);
    QGraphicsScene * scene = new QGraphicsScene;
    _view = new WebView();
    _view->setAcceptHoverEvents(true);
    scene->addItem(_view);
    scene->setActiveWindow(_view);
    QGraphicsView * view= new QGraphicsView(scene,this);
    view->setFrameShape(QFrame::NoFrame);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setLayout(new QVBoxLayout());
    layout()->addWidget(view);
    layout()->setMargin(0);
    _view->setUrl(QUrl::fromLocalFile(QFileInfo("html/index.html").absoluteFilePath()));
    connect(_view->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addInterface()));
    connect(_interface,SIGNAL(close()),this,SLOT(close()));
    connect(_interface,SIGNAL(hide()),this,SLOT(showMinimized()));
    connect(_interface,SIGNAL(restore()),this,SLOT(restore()));
    connect(_interface,SIGNAL(expand()),this,SLOT(expand()));
    setMinimumSize(600,500);
}


void HtmlView::resizeEvent(QResizeEvent *e)
{
    _view->resize(e->size());//Resize view when window is resized
}

void HtmlView::changeEvent(QEvent *e)
{
    if(e->type()==QEvent::WindowStateChange){
        _interface->setRestore(this->isMaximized());
        emit _interface->restoreChanged(this->isMaximized());
    }
}

void HtmlView::addInterface()
{
    _view->page()->mainFrame()->addToJavaScriptWindowObject("interface",_interface);
    QFile script(":/application.js");
    if(script.open(QFile::ReadOnly))
        _view->page()->mainFrame()->evaluateJavaScript(script.readAll());
    script.close();
}

void HtmlView::restore()
{
    this->showNormal();
}

void HtmlView::expand()
{
    this->showMaximized();
}
