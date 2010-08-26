//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QWSServer>
#include <QApplication>
#include <QSettings>
#include <QFile>
#include <QTimer>
#include <QStringList>
#include <QMessageBox>
#include <QSplashScreen>
#include "hac-config.h"
#include "config.h"
#include "hacserver.h"
#include "calibrationdialog.h"
#include "hacwaitbox.h"

static bool firstUse(void)
{
	/* Checking Touch Screen */
	bool needCal = false;
	// the pointercal file  is specified in qte env
	QString calFile = QString::fromLocal8Bit(qgetenv("POINTERCAL_FILE"));
	if (calFile.isEmpty())
		calFile = QLatin1String("/etc/pointercal");

	QFile file(calFile);
	if (file.open(QIODevice::ReadOnly)) {
		// checking pointercal calibration data
		QTextStream t(&file);
		int a,b,c,d,e,f,s = 0;
		t >> a >> b >> c >> d >> e >> f >> s;
		qWarning() << s << t.status();
		if (s == 0 || t.status() != QTextStream::Ok)
			needCal=true;
		file.close();
	} else {
		needCal=true;
	}

	if (needCal) {
		{
			// FIXME: We should implement a custom message box, QMessageBox is too heavy!
			QMessageBox message;
			message.setText("Please press once at each of the marks "
							"shown in the next screen."
							"This messagebox will timout after 10 seconds "
							"if you are unable to close it.");
			QTimer::singleShot(10 * 1000, &message, SLOT(accept()));
			message.exec();
		}

		{
			CalibrationDialog cal;
			cal.exec();
		}
	}

	QSettings config(CONFIG_FILE, QSettings::IniFormat);
	config.beginGroup("Startup");

	if (!config.value("FirstUse", true).toBool())
		return false; // This is not the first use startup.

	qDebug() << "This is FirstUse!";
	// FIXME: We should set this flag to false after some certain steps.
	config.setValue("FirstUse", false);
	config.sync();

	return true;
}

/**
 * HAC Server main entry
 * @param argc: argument count
 * @param argv: argument array
 * @return: 0 on success, otherwise if error happen
 */
int main(int argc, char *argv[])
{
	QApplication app(argc, argv, QApplication::GuiServer);
	qDebug() << "main" << app.arguments();

	QCoreApplication::setOrganizationName(APP_ORG_NAME);
	QCoreApplication::setOrganizationDomain(APP_ORG_DOMAIN);
	QCoreApplication::setApplicationName(APP_NAME);

	//QWSServer::setBackground(Qt::white);
	QWSServer::setBackground(QPixmap(":/hacserver/images/splash.png"));
	app.setQuitOnLastWindowClosed(false);

	if (QWSServer::mouseHandler() == NULL) {
		// maybe we should not just quiting here, a error/warning message would better
		qFatal("No mouse handler installed");
		// we are very sorry that your touch screen is missing!
	}

	firstUse();

    //HacWaitBox wait;
    //wait.setText(HacServer::tr("starting HAC, please wait for a while ..."));
    //wait.show();
    //wait.hide();

	HacServer srv;
	srv.init();

	return app.exec();
}
