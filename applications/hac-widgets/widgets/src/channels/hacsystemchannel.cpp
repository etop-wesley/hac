//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QCopChannel>
#include "hacsystemchannel.h"

#define SYSTEM_CHANNEL_NAME "Hac/System"
#define SYSTEM_MESSAGE_UPDATEBACKGROUND "updateBackground()"
#define SYSTEM_MESSAGE_EXPORTBACKGROUND "exportBackground()"

/*
 * HAC System Channel Server
 */
class HacSystemChannelServerPrivate : public QCopChannel
{
    Q_OBJECT
public:
	HacSystemChannelServerPrivate(HacSystemChannelServer *parent)
	: QCopChannel(SYSTEM_CHANNEL_NAME, parent), q(parent) {}

	~HacSystemChannelServerPrivate() {}

    void receive(const QString&message, const QByteArray &data);

private:
	HacSystemChannelServer *q;
};

void HacSystemChannelServerPrivate::receive(const QString&message, const QByteArray &data)
{
	qDebug() << "HacSystemChannelServerPrivate::receive" << message << data;
    QDataStream in(data);

	if (message == SYSTEM_MESSAGE_UPDATEBACKGROUND) {
	} else if (message == SYSTEM_MESSAGE_EXPORTBACKGROUND) {
	}
}



HacSystemChannelServer::HacSystemChannelServer(QObject *parent)
: QObject(parent), d(new HacSystemChannelServerPrivate(this))
{
}

HacSystemChannelServer::~HacSystemChannelServer()
{
	delete d;
}


/*
 * HAC System Channel Client
 */
class HacSystemChannelClientPrivate : public QCopChannel
{
    Q_OBJECT
public:
	HacSystemChannelClientPrivate(HacSystemChannelClient *parent)
	: QCopChannel(SYSTEM_CHANNEL_NAME, parent), q(parent) {}

	~HacSystemChannelClientPrivate() {}

    void receive(const QString&message, const QByteArray &data);

private:
	HacSystemChannelClient *q;
};

void HacSystemChannelClientPrivate::receive(const QString&message, const QByteArray &data)
{
	qDebug() << "HacSystemChannelClientPrivate::receive" << message << data;
}


HacSystemChannelClient::HacSystemChannelClient(QObject *parent)
: QObject(parent), d(new HacSystemChannelClientPrivate(this))
{
}

HacSystemChannelClient::~HacSystemChannelClient()
{
	delete d;
}

void HacSystemChannelClient::updateBackground()
{
	QCopChannel::send(SYSTEM_CHANNEL_NAME, SYSTEM_MESSAGE_UPDATEBACKGROUND);
}

void HacSystemChannelClient::exportBackground()
{
	QCopChannel::send(SYSTEM_CHANNEL_NAME, SYSTEM_MESSAGE_EXPORTBACKGROUND);
}

#include "hacsystemchannel.moc"

