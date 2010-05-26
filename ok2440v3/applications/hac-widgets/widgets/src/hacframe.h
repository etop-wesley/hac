#ifndef _HACFRAME_H_
#define _HACFRAME_H_

#include "hacwidgetglobal.h"
#include <QtGui/QFrame>

class HacFramePrivate;

class HACWIDGET_EXPORT HacFrame : public QFrame {
	Q_OBJECT

public:
	HacFrame(QWidget *parent = NULL, Qt::WindowFlags f = 0);
	~HacFrame();

private:
	HacFramePrivate *d;
};

#endif // _HACFRAME_H_
