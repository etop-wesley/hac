//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>

#include "hacserver.h"
#include <QString>
#include <QByteArray>
#include <QWSServer>
#include <QWSClient>
#include <QScreen>
#include <QWSWindow>

HacServer::HacServer(QObject *parent)
: QObject(parent)
{
    qDebug() << "HacServer::HacServer";
	server = QWSServer::instance();
	QScreen *screen = QScreen::instance();
	server->setMaxWindowRect(QRect(0, 0, screen->width(), screen->height()));
}

HacServer::~HacServer()
{
    qDebug() << "HacServer::~HacServer";

}

void HacServer::init()
{

}
