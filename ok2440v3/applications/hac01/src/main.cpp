//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>

#include "hac-config.h"

#if defined(BUILD_HOST)
	#include <QDesktopWidget>
	#include <QSettings>
	#include <QFile>
#endif

#include <QTextCodec>
#include <QWSServer>
#include <QMessageBox>
#include <QTimer>
#include <QFile>

#include "gui/gui.h"
#include "gui/hacapplication.h"
#include "gui/hacmainwindow.h"

#include "calibrationdialog.h"
#include "scribblewidget.h"



/**
 * main entry
 * @param argc: argument count
 * @param argv: argument array
 * @return: 0 on success, otherwise if error happen
 */
int main(int argc, char *argv[])
{
	HacApplication app(argc, argv);
	qDebug() << "main" << app.arguments();
	// the resources are listed in hac.qrc 
	Q_INIT_RESOURCE(hac);

#if !defined(BUILD_HOST)
	// check mouse calibration

	if (!QWSServer::mouseHandler())
		qFatal("No mouse handler installed");


	QString calfile(getenv("TSLIB_CALIBFILE"));
	if (calfile.isEmpty())
		calfile = QString ("/usr/etc/pointercal");

	if (!QFile::exists(calfile)) {
		{
			QMessageBox message;
			message.setText("<p>Please press once at each of the marks "
							"shown in the next screen.</p>"
							"<p>This messagebox will timout after 10 seconds "
							"if you are unable to close it.</p>");
			QTimer::singleShot(10 * 1000, &message, SLOT(accept()));
			message.exec();
		}

		{
			CalibrationDialog cal;
			cal.exec();
		}

		{
			QMessageBox message;
			message.setText("<p>The next screen will let you test the calibration "
							"by drawing into a widget.</p><p>This program will "
							"automatically close after 20 seconds.<p>");
			QTimer::singleShot(10 * 1000, &message, SLOT(accept()));
			message.exec();
		}

		//ScribbleWidget scribble;
		//scribble.showMaximized();
		//app.setActiveWindow(&scribble);
		//QTimer::singleShot(20 * 1000, &scribble, SLOT(close()));
	}
#endif
	// start main window

    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF8"));

	app.showWindow("HacStatusWidget");
	app.showWindow("MainHomePage");

	int r = app.exec();

	Q_CLEANUP_RESOURCE(hac);
	return r;
}
