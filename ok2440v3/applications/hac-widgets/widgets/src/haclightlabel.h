#ifndef _HACLIGHTLABEL_H_
#define _HACLIGHTLABEL_H_

#include "hacwidgetglobal.h"
#include <QtGui/QLabel>

class HacLightLabelPrivate;

class HACWIDGET_EXPORT HacLightLabel : public QLabel {
	Q_OBJECT

	Q_PROPERTY(int minimum READ minimum WRITE setMinimum)
	Q_PROPERTY(int maximum READ maximum WRITE setMaximum)
	Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged USER true)

public:
	HacLightLabel(QWidget *parent = 0);
	~HacLightLabel();

	int minimum() const;
	int maximum() const;
	int value() const;

Q_SIGNALS:
	void rangeChanged(int minimum, int maximum);
	void valueChanged(int value);

public Q_SLOTS:
	void reset();
	void setMinimum(int minimum);
	void setMaximum(int maximum);
	void setRange(int minimum, int maximum);
	void setValue(int value);

protected:

private Q_SLOTS:

private:
	void do_light_adjust(QImage *image, int factor);

private:
	HacLightLabelPrivate *d;
};

#endif // _HACLIGHTLABEL_H_
