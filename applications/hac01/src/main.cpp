//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QWSServer>
#include <QFile>
#include <QTimer>
#include <QMessageBox>
#include <QSplashScreen>

#include "hac-config.h"
#include "gui/gui.h"
#include "gui/hacapplication.h"
#include "gui/mainwindow.h"
#include "settings/calibrationdialog.h"

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
    // the resources are listed in hac01.qrc 
    Q_INIT_RESOURCE(hac01);

    // show splash screen
    QSplashScreen *splash = new QSplashScreen(QPixmap(":/HAC01/hac01-splash.png"));
    splash->show();
    app.processEvents();

    /*
     * checking input device
     */
    // check mouse calibration
    if (QWSServer::mouseHandler() == NULL) {
        // maybe we should not just quiting here, a error/warning message would better
        qFatal("No mouse handler installed");
    }

    // the pointercal file path is specified in qt env
    QString calfile(getenv("POINTERCAL_FILE"));

    if (!QFile::exists(calfile)) {
        {
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

    MainWindow mw;
    mw.showMaximized();

    app.processEvents();

    // close splash screen;
    splash->finish(&mw);
    delete splash;
    splash = NULL;

    int r = app.exec();
    Q_CLEANUP_RESOURCE(hac01);
    return r;
}
