#ifndef _HACSCROLLAREA_H_
#define _HACSCROLLAREA_H_

#include "hacwidgetglobal.h"
#include <QtGui/QScrollArea>

class HacScrollAreaPrivate;

class HACWIDGET_EXPORT HacScrollArea : public QScrollArea {
	Q_OBJECT

public:
	HacScrollArea(QWidget *parent = NULL);
	~HacScrollArea();

private:
	HacScrollAreaPrivate *d;
};

#endif // _HACSCROLLAREA_H_
