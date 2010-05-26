//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QTimer>
#include <QPainter>
#include <QPoint>
#include <QColor>
#include <QTime>
#include <QTransform>
#include <QMouseEvent>
#include <math.h>
#include "hachelp.h"



#include "hactempinputdialog.h"
#include "hacanalogclockpickwidget.h"
#include "hacanalogclockpickwidget_p.h"

#define TOTAL_HOURS 24
#define ANGLE_PER_HOUR (360.0/TOTAL_HOURS)


#define CLOCKANGLE_2_STDANGLE(a) ((a) <= 90 ? (90.0 - (a)) : (360.0 - ((a) - 90.0)))
#define STDANGLE_2_CLOCKANGLE(a) ((a) <= 90 ? (90.0 - (a)) : (360.0 - ((a) - 90.0)))


HacAnalogClockPickWidget::HacAnalogClockPickWidget(QWidget *parent)
    : QWidget(parent)
{
	d = new HacAnalogClockPickWidgetPrivate;
	d->precision = Precision_HalfHour;
	d->picking = false;
	d->textVisible = true;
}

HacAnalogClockPickWidget::~HacAnalogClockPickWidget()
{
	delete d;
}


HacAnalogClockPickWidget::Precision HacAnalogClockPickWidget::precision() const
{
	return d->precision;
}

void HacAnalogClockPickWidget::setPrecision(Precision precision)
{
	if (precision != d->precision) {
		 d->precision = precision;
		 update();
	}
}

bool HacAnalogClockPickWidget::isTextVisible() const
{
	return d->textVisible;
}

void HacAnalogClockPickWidget::setTextVisible(bool visible)
{
	if (visible != d->textVisible) {
		d->textVisible = visible;
		update();
	}
}

QList<HacAnalogClockPickWidget::PickedItemData> HacAnalogClockPickWidget::pickedList() const
{
	return d->pickedList;
}

void HacAnalogClockPickWidget::setPickedList(const QList<PickedItemData> &list)
{
	if (list != d->pickedList) {
		d->pickedList = list;
		update();
	}
}

QTime HacAnalogClockPickWidget::timeFromPos(const QPoint &p)
{
	// get angle from position refer to origin
	QPoint o(width() / 2, height() / 2);
	qreal angle = HacHelp::RadianToAngle(atan2(o.y() - p.y(), p.x() - o.x()));
	if (angle < 0) angle += 360.0; // to positive angle value
	angle = STDANGLE_2_CLOCKANGLE(angle);
	qDebug() << angle;
	// get time from angle
	int hour = -1, minute = -1, second = -1;
	qreal rest;
	switch (d->precision) {
	case Precision_OneHour:
		hour = angle / ANGLE_PER_HOUR;
		rest = angle - ANGLE_PER_HOUR * hour;
		if (rest > ANGLE_PER_HOUR / 2)
			hour += 1;
		minute = 0;
		second = 0;
		break;
	case Precision_HalfHour:
		hour = angle / ANGLE_PER_HOUR;
		rest = angle - ANGLE_PER_HOUR * hour;
		if (rest <= ANGLE_PER_HOUR / 4)
			minute = 0;
		else if (rest > ANGLE_PER_HOUR / 4 && rest <= ANGLE_PER_HOUR * 3 / 4)
			minute = 30;
		else
			minute = 0, hour += 1;
		second = 0;
		break;
	case Precision_QuarterHour:
		hour = angle / ANGLE_PER_HOUR;
		rest = angle - ANGLE_PER_HOUR * hour;
		if (rest <= ANGLE_PER_HOUR / 8)
			minute = 0;
		else if (rest > ANGLE_PER_HOUR / 8 && rest <= ANGLE_PER_HOUR * 3 / 8)
			minute = 15;
		else if (rest > ANGLE_PER_HOUR * 3 / 8 && rest <= ANGLE_PER_HOUR * 5 / 8)
			minute = 30;
		else if (rest > ANGLE_PER_HOUR * 5 / 8 && rest <= ANGLE_PER_HOUR * 7 / 8)
			minute = 45;
		else
			minute = 0, hour += 1;
		second = 0;
		break;
	default:
		break;
	}

	return QTime(hour, minute, second);
}

void HacAnalogClockPickWidget::checking_and_adding_item(const PickedItemData &item)
{
	d->pickedList.append(item);
}


void HacAnalogClockPickWidget::mouseDoubleClickEvent(QMouseEvent * e)
{
	qDebug() << "HacAnalogClockPickWidget::mouseDoubleClickEvent";
	QWidget::mouseDoubleClickEvent(e);
}

void HacAnalogClockPickWidget::mousePressEvent(QMouseEvent *e)
{
	qDebug() << "HacAnalogClockPickWidget::mousePressEvent";
	QWidget::mousePressEvent(e);

	d->picking = true;
	d->pickingStart = timeFromPos(e->pos());
	d->pickingEnd = d->pickingStart;
	update();
}

void HacAnalogClockPickWidget::mouseReleaseEvent(QMouseEvent *e)
{
	qDebug() << "HacAnalogClockPickWidget::mouseReleaseEvent";
	QWidget::mouseReleaseEvent(e);

	d->picking = false;
	d->pickingEnd = timeFromPos(e->pos());
	update();

	HacTempInputDialog dialog;
	dialog.setStart(d->pickingStart.toString());
	dialog.setEnd(d->pickingEnd.toString());
	dialog.move(0, 60);
	if (dialog.exec() == QDialog::Accepted) {
		int temp = dialog.temp();
		PickedItemData item(d->pickingStart, d->pickingEnd, temp);
		checking_and_adding_item(item);
		update();
	}
}

void HacAnalogClockPickWidget::mouseMoveEvent(QMouseEvent *e)
{
	qDebug() << "HacAnalogClockPickWidget::mouseMoveEvent";
	QWidget::mouseMoveEvent(e);
	if (d->picking) {
		d->pickingEnd = timeFromPos(e->pos());
	}
	update();
}

void HacAnalogClockPickWidget::paintEvent(QPaintEvent *)
{
	qDebug() << "HacAnalogClockPickWidget::paintEvent";

	const int textMargin = 0;
	QRect crect = contentsRect();
	int side =  qMin(crect.width(), crect.height());
	QRect textRect = QFontMetrics(font()).boundingRect("XX");
    QPoint origin = crect.center();
    int radius = side / 2 - qMax(textRect.width(), textRect.height()) - textMargin;

	QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
	QColor hourColor(127, 0, 127);

    painter.save();
	// draw round rect
	QPen  rp(Qt::gray, 3);
	painter.setPen(rp);
	painter.drawEllipse(origin, radius+5, radius+5);
    // draw tick
    painter.translate(crect.center());
	painter.setBrush(hourColor);
	switch (d->precision) {
	case Precision_OneHour:
		painter.rotate(-90.0);
        for (int i = 0; i < TOTAL_HOURS; ++i) {
			painter.drawLine(radius - 10, 0, radius, 0);
			painter.rotate(ANGLE_PER_HOUR);
		}
		break;
	case Precision_HalfHour:
		painter.rotate(-90.0);
        for (int i = 0; i < TOTAL_HOURS; ++i) {
			painter.drawLine(radius - 10, 0, radius, 0);
			painter.rotate(ANGLE_PER_HOUR / 2);
			painter.drawLine(radius - 7, 0, radius, 0);
			painter.rotate(ANGLE_PER_HOUR / 2);
		}
		break;
	case Precision_QuarterHour:
		painter.rotate(-90.0);
        for (int i = 0; i < TOTAL_HOURS; ++i) {
			painter.drawLine(radius - 10, 0, radius, 0);
			painter.rotate(ANGLE_PER_HOUR / 4);
			painter.drawLine(radius - 4, 0, radius, 0);
			painter.rotate(ANGLE_PER_HOUR / 4);
			painter.drawLine(radius - 7, 0, radius, 0);
			painter.rotate(ANGLE_PER_HOUR / 4);
			painter.drawLine(radius - 4, 0, radius, 0);
			painter.rotate(ANGLE_PER_HOUR / 4);
		}
		break;
	default:
		break;
	}
    painter.restore();

	// draw tick text
	if (d->textVisible) {
		qreal radius_ext = radius;
		qreal dr = qMax(textRect.width(), textRect.height());
		radius_ext += dr;

		painter.save();
		qreal a = 0;
		qreal da = HacHelp::AngleToRadian(15.0);
		for (int i = 0; i < 24; ++i) {
			int dx = radius_ext * sin(a);
			int dy = radius_ext * cos(a);
			QPoint p(origin.x() + dx, origin.y() - dy);
            textRect.moveCenter(p);
			painter.drawText(textRect, Qt::AlignCenter, QString::number(i));
			a += da;
		}
		painter.restore();
	}

	// draw picked areas
	if (!d->pickedList.isEmpty()) {
		for (int i = 0; i < d->pickedList.size(); i++) {
			PickedItemData item = d->pickedList[i];
			qreal startClockAngle = ANGLE_PER_HOUR * item.start().hour() + ANGLE_PER_HOUR / 4 * (item.start().minute() / 15);
			qreal endClockAngle = ANGLE_PER_HOUR * item.end().hour() + ANGLE_PER_HOUR / 4 * (item.end().minute() / 15);

			qreal startAngle = CLOCKANGLE_2_STDANGLE(startClockAngle);
			qreal endAngle = CLOCKANGLE_2_STDANGLE(endClockAngle);
			qreal spanAngle = -(endClockAngle - startClockAngle);

			// draw start line
			QPen pen(QColor(0, 0, 250), 1);
			painter.setPen(pen);
			painter.save();
			painter.translate(origin);
			painter.rotate(-startAngle);
			painter.drawLine(radius - 2, 0, 0, 0);
			painter.restore();
			// draw end line
			painter.save();
			painter.translate(origin);
			painter.rotate(-endAngle);
			painter.drawLine(radius - 2, 0, 0, 0);
			painter.restore();

			// draw area
			QRectF rect(0, 0, 2*radius+10, 2*radius+10);
			rect.moveCenter(origin);
            QPainterPath piePath;
			piePath.moveTo(origin);
			piePath.arcTo(rect, startAngle, spanAngle);
			painter.fillPath(piePath, QColor(0, 0, 200, 127));
			// draw value
			painter.save();
			QPen vpen(Qt::white, 2);
			painter.setPen(vpen);
			qreal a = HacHelp::AngleToRadian((startClockAngle + endClockAngle)/2);
			qreal r = radius * 2 / 3;
			int dx = r * sin(a);
			int dy = r * cos(a);
			QPoint p(origin.x() + dx, origin.y() - dy);
			QRect vTxtRect = QFontMetrics(font()).boundingRect("XXX");
			vTxtRect.moveCenter(p);
			painter.drawText(vTxtRect, Qt::AlignCenter, QString::number(item.value()));
			painter.restore();
		}
	}

	// draw picking area
	if (d->picking) {
		qreal startClockAngle = ANGLE_PER_HOUR * d->pickingStart.hour() + ANGLE_PER_HOUR / 4 * (d->pickingStart.minute() / 15);
		qreal endClockAngle = ANGLE_PER_HOUR * d->pickingEnd.hour() + ANGLE_PER_HOUR / 4 * (d->pickingEnd.minute() / 15);

		qreal startAngle = CLOCKANGLE_2_STDANGLE(startClockAngle);
		qreal endAngle = CLOCKANGLE_2_STDANGLE(endClockAngle);
		qreal spanAngle = -(endClockAngle - startClockAngle);

		// draw start line
		QPen pen(QColor(255, 0, 0), 2);
		painter.setPen(pen);
		painter.save();
		painter.translate(origin);
		painter.rotate(-startAngle);
		painter.drawLine(radius - 2, 0, 0, 0);
		painter.restore();
		// draw end line
		painter.save();
		painter.translate(origin);
		painter.rotate(-endAngle);
		painter.drawLine(radius - 2, 0, 0, 0);
		painter.restore();

		QRectF rect(0, 0, 2*radius +10, 2*radius +10);
		rect.moveCenter(origin);

		QPainterPath piePath;
		piePath.moveTo(origin);
		piePath.arcTo(rect, startAngle, spanAngle);
		painter.fillPath(piePath, QColor(225, 0, 0, 127));
	}
}

HacAnalogClockPickWidgetPrivate::HacAnalogClockPickWidgetPrivate()
{
}

HacAnalogClockPickWidgetPrivate::~HacAnalogClockPickWidgetPrivate()
{
}
