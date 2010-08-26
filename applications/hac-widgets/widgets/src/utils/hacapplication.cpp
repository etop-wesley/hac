//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QStringList>
#include <QWidget>
#include "hacapplication.h"

HacApplication::HacApplication(int &argc, char **argv)
: QApplication(argc, argv)
{
	qDebug() << "HacApplication::HacApplication" << arguments();
	init();
}

HacApplication::HacApplication(int &argc, char **argv, bool GUIenabled)
: QApplication(argc, argv, GUIenabled)
{
	qDebug() << "HacApplication::HacApplication" << arguments();
	init();
}

HacApplication::HacApplication(int &argc, char **argv, Type type)
: QApplication(argc, argv, type)
{
	qDebug() << "HacApplication::HacApplication" << arguments();
	init();
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

void HacApplication::init()
{
	qDebug() << "HacApplication::init";
	applyStyle();
}

void HacApplication::applyStyle()
{
	qDebug() << "HacApplication::applyStyle";

    QApplication::setStyle("HacStyle");
}

/*
 * find window(top level widget) in application by object name
 */
QWidget * HacApplication::findWindow(const QString &name)
{
	qDebug() << "HacApplication::applyStyle" << name;
	foreach (QWidget *widget, QApplication::topLevelWidgets()) {
		if (widget->objectName() == name)
			return widget;
	}
	return NULL;
}

/*
 * find widget(include window) in application by object name
 */
QWidget * HacApplication::findWidget(const QString &name)
{
	foreach (QWidget *widget, QApplication::allWidgets()) {
		if (widget->objectName() == name)
			return widget;
	}
	return NULL;
}


