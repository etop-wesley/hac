#ifndef _HACAPPLICATION_H_
#define _HACAPPLICATION_H_

#include <QApplication>

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
	HacApplication(int &argc, char **argv, bool GUIenabled);
	HacApplication(int &argc, char **argv, Type type);

	~HacApplication();

	static HacApplication * instance();

	static QWidget * findWindow(const QString &name);
	static QWidget * findWidget(const QString &name);

	static void applyStyle();

Q_SIGNALS:

public Q_SLOTS:

protected:

private Q_SLOTS:

private:
	void init();

private:

};

#endif // _HACAPPLICATION_H_
