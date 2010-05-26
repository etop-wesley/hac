#include <QDebug>
#include <QMouseEvent>
#include <QEvent>
#include <QPoint>
#include "haclabel.h"
#include "haclabel_p.h"

HacLabel::HacLabel(QWidget * parent, Qt::WindowFlags f)
: QLabel(parent, f), d(new HacLabelPrivate)
{

}

HacLabel::HacLabel(const QString & text, QWidget *parent, Qt::WindowFlags f)
: QLabel(text, parent, f), d(new HacLabelPrivate)
{

}


HacLabel::~HacLabel()
{
	if (d != NULL) {
		delete d;
		d = NULL;
	}
}

bool HacLabel::isClickable() const
{
	return d->clickable;
}

void HacLabel::setClickable(bool clickable)
{
	if (clickable != d->clickable) {
		d->clickable = clickable;
	}
}

void HacLabel::mouseDoubleClickEvent(QMouseEvent * e)
{
	if (e->button() == Qt::LeftButton)
		emit doubleClicked();
	QLabel::mouseDoubleClickEvent(e);
}


void HacLabel::mousePressEvent(QMouseEvent * e)
{
	if (e->button() == Qt::LeftButton) {
		d->pressed = true;
	} else
		d->pressed = false;
	emit pressed();
}


void HacLabel::mouseReleaseEvent(QMouseEvent * e)
{
	if (d->pressed && e->button() == Qt::LeftButton && hitLabel(e->pos()))
		emit clicked();
	d->pressed = false;
	emit released();
}

void HacLabel::enterEvent(QEvent *e)
{
	QLabel::enterEvent(e);
	emit mouseOver();
}

void HacLabel::leaveEvent(QEvent *e)
{
	QLabel::leaveEvent(e);
	emit mouseOut();
}

bool HacLabel::hitLabel(const QPoint & p)
{
	return rect().contains(p);
}

HacLabelPrivate::HacLabelPrivate()
{
}

HacLabelPrivate::~HacLabelPrivate()
{

}



