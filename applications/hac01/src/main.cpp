//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QStringList>

#include "hacapplication.h"
#include "homepage.h"

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

	HomePage home;
	home.showMaximized();

    int r = app.exec();
    Q_CLEANUP_RESOURCE(hac01);
    return r;
}
