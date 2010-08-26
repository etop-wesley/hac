//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>

#include <QString>
#include <QByteArray>
#include <QWSServer>
#include <QWSClient>
#include <QScreen>
#include <QWSWindow>
#include <QProcess>
#include "hac-config.h"
#include "hacserver.h"
#include "statusbar.h"

HacServer::HacServer(QObject *parent)
: QObject(parent)
{
	qDebug() << "HacServer::HacServer";
	// init qws server
	server = QWSServer::instance();
	QScreen *screen = QScreen::instance();
	server->setMaxWindowRect(QRect(WINDOW_X, WINDOW_Y, WINDOW_W, WINDOW_H));

	// init status bar 
	statusBar = new StatusBar;
	connect(statusBar, SIGNAL(homeClicked()), this, SLOT(OnHomeClicked()));
	connect(statusBar, SIGNAL(backClicked()), this, SLOT(OnBackClicked()));
	connect(statusBar, SIGNAL(clockClicked()), this, SLOT(OnClockClicked()));
	statusBar->setGeometry(STATUSBAR_X, STATUSBAR_Y, STATUSBAR_W, STATUSBAR_H);
	statusBar->show();

	// init auto start applications


    QProcess *myApp = new QProcess;
    myApp->setProcessChannelMode(QProcess::ForwardedChannels);
	myApp->start(APP_HAC01_BIN);
	myApp->waitForStarted();
}

HacServer::~HacServer()
{
	qDebug() << "HacServer::~HacServer";

	delete statusBar;
}

void HacServer::init()
{

}

void HacServer::windowEventHandler(QWSWindow *window, QWSServer::WindowEvent eventType)
{
	qDebug() << "HacServer::windowEventHandler" << window->name();
}

void HacServer::OnHomeClicked()
{
	qDebug() << "HacServer::OnHomeClicked";

}

void HacServer::OnBackClicked()
{
	qDebug() << "HacServer::OnBackClicked";

}

void HacServer::OnClockClicked()
{
	qDebug() << "HacServer::OnClockClicked";
}

