#ifndef _HACSYSTEMCHANNEL_H_
#define _HACSYSTEMCHANNEL_H_

#include <QObject>

class HacSystemChannelServerPrivate;

class HacSystemChannelServer : public QObject
{
    Q_OBJECT
public:
    explicit HacSystemChannelServer(QObject *parent = NULL);
    ~HacSystemChannelServer();

Q_SIGNALS:

public Q_SLOTS:

private Q_SLOTS:

private:
	HacSystemChannelServerPrivate *d;
};

class HacSystemChannelClientPrivate;

class HacSystemChannelClient : public QObject
{
    Q_OBJECT
public:
    explicit HacSystemChannelClient(QObject *parent = NULL);
    ~HacSystemChannelClient();

	static void updateBackground();
	static void exportBackground();

Q_SIGNALS:

public Q_SLOTS:

private Q_SLOTS:

private:
	HacSystemChannelClientPrivate *d;
};

#endif // NMEDIAKEYCHANNEL_H

