#include <QDebug>
#include "haclightlabel.h"
#include "haclightlabel_p.h"
#include <QLinearGradient>
#include <QImage>
#include <QPainter>

HacLightLabel::HacLightLabel(QWidget *parent)
: QLabel(parent), d(new HacLightLabelPrivate)
{
    d->minimum = -100;
    d->maximum = 100;
	d->value = 0;
	d->image = new QImage(":/HacWidgets/l1.png");
	setPixmap(QPixmap::fromImage(*d->image));
}

HacLightLabel::~HacLightLabel()
{
	if (d != NULL) {
		delete d->image;
		delete d;
		d = NULL;
	}
}

int HacLightLabel::minimum() const
{
	return d->minimum;
}

int HacLightLabel::maximum() const
{
	return d->maximum;
}

int HacLightLabel::value() const
{
	return d->value;
}

void HacLightLabel::reset()
{

}

void HacLightLabel::setMinimum(int minimum)
{
	if (minimum != d->minimum) {
		d->minimum = minimum;
		if (d->maximum < d->minimum)
			d->maximum = d->minimum;
	}
}

void HacLightLabel::setMaximum(int maximum)
{
	if (maximum != d->maximum) {
		d->maximum = maximum;
		if (d->minimum > d->maximum)
			d->minimum = d->maximum;
	}
}

void HacLightLabel::setRange(int minimum, int maximum)
{
    int oldMin = d->minimum;
    int oldMax = d->maximum;
    d->minimum = minimum;
    d->maximum = qMax(minimum, maximum);
    if (oldMin != d->minimum || oldMax != d->maximum) {
        emit rangeChanged(d->minimum, d->maximum);
        setValue(d->value); // re-bound
    }
}

void HacLightLabel::setValue(int value)
{
	qDebug() << "HacLightLabel::do_light_adjust" << value;

	value = qBound(d->minimum, value, d->maximum);
	if (d->value == value)
		return;

	// test!
	QString file = QString(":/HacWidgets/%1.jpg").arg(d->value);
	setPixmap(QPixmap(file));
	return;

	d->value = value;
	if (d->image != NULL && !d->image->isNull()) {
		QImage img(*d->image);
        do_light_adjust(&img, d->value);
		setPixmap(QPixmap::fromImage(img));
	}

	emit valueChanged(value);
}

void HacLightLabel::do_light_adjust(QImage *image, int factor)
{
	qDebug() << "HacLightLabel::do_light_adjust" << factor;
	if (image == NULL || image->isNull() || factor == 0)
		return;

	int bytes_per_pixel = image->bytesPerLine() / image->width();

	uchar *pixel = NULL;
	QRgb *rgba;

	if (factor > 0) {
		factor += 100;
		for (int h = 0; h < image->height(); h++) {
			pixel = image->scanLine(h);
			for (int w = 0; w < image->width(); w++) {
				rgba = (QRgb *)pixel;
				if (qAlpha(*rgba) != 0 && (qRed(*rgba) != 0 || qGreen(*rgba) != 0 || qBlue(*rgba) != 0))
					*rgba = QColor::fromRgba(*rgba).lighter(factor).rgba();
				pixel += bytes_per_pixel;
			}
		}
	} else {
		factor = -factor;
		factor += 100;
		for (int h = 0; h < image->height(); h++) {
			uchar *pixel = image->scanLine(h);
			for (int w = 0; w < image->width(); w++) {
				rgba = (QRgb *)pixel;
				if (qAlpha(*rgba) != 0 && (qRed(*rgba) != 0 || qGreen(*rgba) != 0 || qBlue(*rgba) != 0))
					*rgba = QColor::fromRgba(*rgba).darker(factor).rgba();
				pixel += bytes_per_pixel;
			}
		}
	}
}



HacLightLabelPrivate::HacLightLabelPrivate()
{
}

HacLightLabelPrivate::~HacLightLabelPrivate()
{

}



