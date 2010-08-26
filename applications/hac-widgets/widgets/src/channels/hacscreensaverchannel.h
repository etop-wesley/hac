#ifndef _HACSCREENSAVERCHANNEL_H_
#define _HACSCREENSAVERCHANNEL_H_

#include <QCopChannel>

class HacScreenSaverServer : public QCopChannel
{
    Q_OBJECT

public:
    explicit HacScreenSaverServer(QObject *parent = NULL);
    ~HacScreenSaverServer();

    void receive(const QString &message, const QByteArray &data);

Q_SIGNALS:

public Q_SLOTS:

private Q_SLOTS:

private:

private:

};

class HacScreenSaverClient : public QCopChannel
{
    Q_OBJECT
public:
    explicit HacScreenSaverClient( QObject *parent = NULL);
    ~HacScreenSaverClient();

Q_SIGNALS:

public Q_SLOTS:

private Q_SLOTS:
	void OnReceiveD(const QString &, const QByteArray &);

private:
	QCopChannel *channel;
};


#endif
