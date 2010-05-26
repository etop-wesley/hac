#include <QDebug>
#include <QMouseEvent>
#include "haclineedit.h"
#include "haclineedit_p.h"

HacLineEdit::HacLineEdit(QWidget *parent)
: QLineEdit(parent), d(new HacLineEditPrivate)
{
}

HacLineEdit::HacLineEdit(const QString & contents, QWidget * parent)
: QLineEdit(contents, parent), d(new HacLineEditPrivate)
{

}

HacLineEdit::~HacLineEdit()
{
	if (d != NULL) {
		delete d;
		d = NULL;
	}
}

void HacLineEdit::mousePressEvent( QMouseEvent *e)
{
	qDebug() << "HacLineEdit::mousePressEvent";
}

void HacLineEdit::mouseMoveEvent(QMouseEvent *e)
{
	qDebug() << "HacLineEdit::mouseMoveEvent";
}

void HacLineEdit::mouseReleaseEvent( QMouseEvent *e)
{
	qDebug() << "HacLineEdit::mouseReleaseEvent";
}

void HacLineEdit::mouseDoubleClickEvent(QMouseEvent *e)
{
	qDebug() << "HacLineEdit::mouseDoubleClickEvent";
}




HacLineEditPrivate::HacLineEditPrivate()
{
}

HacLineEditPrivate::~HacLineEditPrivate()
{

}



