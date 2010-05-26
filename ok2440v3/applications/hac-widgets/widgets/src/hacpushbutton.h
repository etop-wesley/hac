#ifndef _HACPUSHBUTTON_H_
#define _HACPUSHBUTTON_H_

#include "hacwidgetglobal.h"
#include <QtGui/QPushButton>

class HacPushButtonPrivate;

class HACWIDGET_EXPORT HacPushButton : public QPushButton {
	Q_OBJECT

public:
	HacPushButton(QWidget *parent = 0);
	HacPushButton(const QString &text, QWidget * parent = 0);
	HacPushButton(const QIcon &icon, const QString &text, QWidget *parent = 0);
	~HacPushButton();

private:
	HacPushButtonPrivate *d;

};

#endif // _HACPUSHBUTTON_H_
