#ifndef _HACSCROLLBAR_H_
#define _HACSCROLLBAR_H_

#include "hacwidgetglobal.h"
#include <QtGui/QScrollBar>

class HacScrollBarPrivate;

class HACWIDGET_EXPORT HacScrollBar : public QScrollBar {
	Q_OBJECT

public:
	HacScrollBar(QWidget *parent = NULL);
	HacScrollBar(Qt::Orientation orientation, QWidget *parent = NULL);
	~HacScrollBar();

private:
	HacScrollBarPrivate *d;

};

#endif // _HACSCROLLBAR_H_
