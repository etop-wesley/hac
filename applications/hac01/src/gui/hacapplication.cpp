//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QStringList>
#include <QSysInfo>
#include <QLibraryInfo>
#include <QMessageBox>
#include "hac-config.h"
#include "gui.h"
#include "hacapplication.h"

HacApplication::HacApplication(int &argc, char **argv)
: QApplication(argc, argv)
{
	qDebug() << "HacApplication::HacApplication" << arguments();

	QCoreApplication::setOrganizationName(HAC_ORG_NAME);
	QCoreApplication::setOrganizationDomain(HAC_ORG_DOMAIN);
	QCoreApplication::setApplicationName(HAC_APP_NAME);
	QCoreApplication::setApplicationVersion(HAC_VER);

    d_mainWindow = NULL;
/*
	d_deviceManager = new HacDeviceManager(this);

	d_deviceManager->init();
	d_deviceManager->searchDevices();
	if (d_deviceManager->allDevices().isEmpty()) {
		// FIXME: ?
		QMessageBox::information(NULL, tr("device error"), tr("Can not find any control device, please check the connection!"));
	}
*/
	setQuitOnLastWindowClosed(true);
}

HacApplication::~HacApplication()
{
	qDebug() << "HacApplication::~HacApplication";
	//d_deviceManager->release();
	//delete d_deviceManager;
}

HacApplication * HacApplication::instance()
{
	static bool check = false;
	static HacApplication *instance = 0;

	if (!check) {
		if (qApp) {
			instance = qobject_cast<HacApplication *>(qApp);
			check = (bool)instance;
		}
	}

	return instance;
}

