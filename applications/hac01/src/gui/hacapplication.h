#ifndef _HACAPPLICATION_H_
#define _HACAPPLICATION_H_

#include <QApplication>
#include "gui/haccore.h"
#include "gui/mainwindow.h"
#include "device/hacdevicemanager.h"

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

    MainWindow * mainWindow() { return d_mainWindow; }
    void setMainWindow(MainWindow *window) { d_mainWindow = window; }

	//HacDeviceManager *deviceManager() { return d_deviceManager; }

Q_SIGNALS:

public Q_SLOTS:

protected:

private Q_SLOTS:

private:

private:
	//HacDeviceManager *d_deviceManager;
    MainWindow *d_mainWindow;
};

#endif // _HACAPPLICATION_H_
