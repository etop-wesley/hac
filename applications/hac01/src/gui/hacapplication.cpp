//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QStringList>
#include <QSysInfo>
#include <QLibraryInfo>
#include <QMessageBox>
#include "config.h"
#include "hacapplication.h"

#include "homepage.h"
#include "roomchoose.h"
#include "autocontrolmain.h"
#include "stagecontrol.h"

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

/*
 * show application window
 * @param name: the window name
 * @return: the pointer to the widget object
 */
QWidget * HacApplication::showWindow(const QString &name)
{
	qDebug() << "HacApplication::showWindow" << name;
	QWidget *widget = NULL;

	foreach (QWidget *w, QApplication::topLevelWidgets()) {
		if (w->objectName() == name) {
			widget = widget;
			break;
		}
	}

	if (widget == NULL) {
		if (name == "HomePage")
			widget = new HomePage;
		else if (name == "RoomChoose")
			widget = new RoomChoose;
		else if (name == "AutoControlMain")
			widget = new AutoControlMain;
		else if (name == "StageControl")
			widget = new StageControl;

		if (widget != NULL) {
#ifdef HAC_PERFORMANCE_FIXUP
			widget->setAttribute(Qt::WA_PaintOnScreen, true);
			//widget->setAttribute(Qt::WA_OpaquePaintEvent, true);
			widget->setAttribute(Qt::WA_NoSystemBackground, true);
			widget->setAutoFillBackground(false);
#endif // HAC_PERFORMANCE_FIXUP
			widget->setAttribute(Qt::WA_DeleteOnClose);
		}
	}

	if (widget != NULL) {
		if (widget->isHidden())
			widget->showMaximized();
	}

	return widget;
}


