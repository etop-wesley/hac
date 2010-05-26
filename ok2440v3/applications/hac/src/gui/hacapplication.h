#ifndef _HACAPPLICATION_H_
#define _HACAPPLICATION_H_

#include <QApplication>
#include "gui/haccore.h"
#include "gui/hacmainwindow.h"


#include "armsys2440kbdthread.h"
#include <QTimer>

/*
 * exporting a global application object
 */
#if defined(HacApp)
#undef HacApp
#endif
#define HacApp (static_cast<HacApplication *>(QCoreApplication::instance()))


class HacApplication : public QApplication {
	Q_OBJECT

public:
	HacApplication(int &argc, char **argv);
	~HacApplication();

    static HacApplication * instance();

	int switchApp() { return d_switchApp; }

Q_SIGNALS:

public Q_SLOTS:

protected:

private Q_SLOTS:
	void on_read_buttons();
	void on_switch_app();

private:

private:
	ArmSys2440KbdThread *kbdThread;
	QTimer *kbdTimer;
	QTimer *switchTimer;
	int d_switchApp;

};

#endif // _HACAPPLICATION_H_
