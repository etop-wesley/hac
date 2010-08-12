//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>

#include "config.h"
#include "gui/hacapplication.h"
#include "gui/mainwindow.h"

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

    //MainWindow mw;
	QWidget *w = app.showWindow("HomePage");
    //mw.showMaximized();

	//app.setMainWindow(&mw);
    app.processEvents();

    int r = app.exec();
    Q_CLEANUP_RESOURCE(hac01);
    return r;
}
