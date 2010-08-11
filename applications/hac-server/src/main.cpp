//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QWSServer>
#include <QApplication>
#include <QStringList>
#include "config.h"
#include "hacserver.h"

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

    app.setQuitOnLastWindowClosed(false);

    HacServer srv;
    srv.init();
    
    return app.exec();
}
