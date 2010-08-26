#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "hacwidget.h"

HacWidget::HacWidget(QWidget *parent, Qt::WindowFlags f)
: QWidget(parent, f)
{
	qDebug() << "HacWidget::HacWidget";
}

HacWidget::~HacWidget()
{
	qDebug() << "HacWidget::~HacWidget";
}

void HacWidget::changeEvent(QEvent * event)
{
	return QWidget::changeEvent(event);
}

void HacWidget::setBackground()
{
	qDebug() << "HacWidget::setBackground";
}

