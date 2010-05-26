//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QStringList>
#include <QSysInfo>
#include <QLibraryInfo>
#include "hac-config.h"
#include "gui.h"
#include "hacapplication.h"
#include "hacstatuswidget.h"
#include "mainhomepage.h"
#include "datetimesettings.h"
#include "mainlightingpage.h"
#include "airconditioningcontrolpage.h"
#include "heatingcontrolpage.h"
#include "curtainscontrolpage.h"
#include "mainstagepage.h"
#include "mainswitchpage.h"
#include "systemmain.h"
#include "acscheduleset.h"
#include "heatingcontrolpage.h"
#include "lightcontrolpage.h"
#include "switchcontrolpage.h"
#include "regionalsettings.h"
#include "datetimesettings.h"
#include "propertiessettings.h"

HacApplication::HacApplication(int &argc, char **argv)
: QApplication(argc, argv)
{
	qDebug() << "HacApplication::HacApplication" << arguments();

	QCoreApplication::setOrganizationName(HAC_ORG_NAME);
	QCoreApplication::setOrganizationDomain(HAC_ORG_DOMAIN);
	QCoreApplication::setApplicationName(HAC_APP_NAME);
	QCoreApplication::setApplicationVersion(HAC_VER);

	QImage bg(":/Hac/background-800x480.png");
	d_backgroundBrush = QBrush(bg.scaled(WINDOW_W, WINDOW_H, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

	setQuitOnLastWindowClosed(true);
}

HacApplication::~HacApplication()
{
	qDebug() << "HacApplication::~HacApplication";
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

void HacApplication::showWindow(const QString &name)
{
	qDebug() << "HacApplication::showWindow" << name;
	QWidget *widget = NULL;
    foreach (QWidget *w, QApplication::topLevelWidgets()) {
		if (w->objectName() == name)
			widget = w;
    }
	
	if (name == "HacStatusWidget") {
		if (widget == NULL) {
			widget = new HacStatusWidget;
			widget->setGeometry(TASKPANEL_X, TASKPANEL_Y, TASKPANEL_W,TASKPANEL_H);
			widget->setAttribute(Qt::WA_DeleteOnClose);

			QImage bg(":/Hac/t1.png");
			QPalette pal = widget->palette();
			pal.setBrush(QPalette::Window, bg.scaled(TASKPANEL_W, TASKPANEL_H, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
			widget->setPalette(pal);
		}

		if (widget != NULL)
			widget->show();

		return;
	}

	if (widget == NULL) {
		if (name == "MainHomePage")
			widget = new MainHomePage;
		else if (name == "DateTimeSettings")
			widget = new DateTimeSettings;
		else if (name == "AirConditioningControlPage")
			widget = new AirConditioningControlPage;
		else if (name == "HeatingControlPage")
			widget = new HeatingControlPage;
		else if (name == "CurtainsControlPage")
			widget = new CurtainsControlPage;
		else if (name == "MainLightingPage")
			widget = new MainLightingPage;
		else if (name == "MainSwitchPage")
			widget = new MainSwitchPage;
		else if (name == "MainStagePage")
			widget = new MainStagePage;
		else if (name == "SystemMain")
			widget = new SystemMain;
		else if (name == "AcScheduleSet")
			widget = new AcScheduleSet, ((AcScheduleSet *)widget)->setTitle(tr("AC Programming"));
		else if (name == "HeatingScheduleSet")
			widget = new AcScheduleSet, ((AcScheduleSet *)widget)->setTitle(tr("Heating Programming"));
		else if (name == "HeatingControlPage")
			widget = new HeatingControlPage;
		else if (name == "LightControlPage")
			widget = new LightControlPage;
		else if (name == "SwitchControlPage")
			widget = new SwitchControlPage;
		else if (name == "RegionalSettings")
			widget = new RegionalSettings;
		else if (name == "DateTimeSettings")
			widget = new DateTimeSettings;
		else if (name == "PropertiesSettings")
			widget = new PropertiesSettings;

		if (widget != NULL) {
			widget->setGeometry(WINDOW_X, WINDOW_Y, WINDOW_W, WINDOW_H);
			widget->setAttribute(Qt::WA_DeleteOnClose);
	
			QPalette pal = widget->palette();
			pal.setBrush(QPalette::Window, HacApp->backgroundBrush());
			widget->setPalette(pal);
		}
	}

	if (widget != NULL)
		widget->show();
}


