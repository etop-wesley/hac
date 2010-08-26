#ifndef _HACSERVER_H_
#define _HACSERVER_H_

/*
 * Window Manager for HAC
 *
 * 1) Initial creation. ----------------------------------- 2010-08-08 wesley.xie
 *
 */

#include <QObject>
#include <QWSServer>
#include <QWSClient>
#include <QWSWindow>

class StatusBar;

class HacServer : public QObject
{
	Q_OBJECT

public:
	HacServer(QObject *parent = NULL);
	~HacServer();

    void init();

Q_SIGNALS:

public Q_SLOTS:

protected:

private Q_SLOTS:
    void windowEventHandler(QWSWindow *, QWSServer::WindowEvent);

	void OnHomeClicked();
	void OnBackClicked();
	void OnClockClicked();

private:
    QWSServer *server;
	StatusBar *statusBar;
};

#endif // _HACSERVER_H_
