#ifndef _HACTABWIDGET_H_
#define _HACTABWIDGET_H_

#include "hacwidgetglobal.h"
#include <QtGui/QTabWidget>

class HacTabWidgetPrivate;

class HACWIDGET_EXPORT HacTabWidget : public QTabWidget {
	Q_OBJECT

public:
	HacTabWidget(QWidget *parent = 0);
	~HacTabWidget();

private:
	HacTabWidgetPrivate *d;

};

#endif // _HACTABWIDGET_H_
