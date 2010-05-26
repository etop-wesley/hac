#ifndef _HACAPPLICATION_H_
#define _HACAPPLICATION_H_

#include <QApplication>
#include "gui/haccore.h"
#include "gui/hacmainwindow.h"

/*
 * exporting a global application object
 */
#if defined(HacApp)
#undef HacApp
#endif
#define HacApp (static_cast<HacApplication *>(QCoreApplication::instance()))


class HacApplication : public QApplication {
	Q_OBJECT

public:
	HacApplication(int &argc, char **argv);
	~HacApplication();

    static HacApplication * instance();

	const QBrush & backgroundBrush() const { return d_backgroundBrush; }

	void showWindow(const QString &name);

Q_SIGNALS:

public Q_SLOTS:

protected:

private Q_SLOTS:

private:

private:
	QBrush d_backgroundBrush;
};

#endif // _HACAPPLICATION_H_
