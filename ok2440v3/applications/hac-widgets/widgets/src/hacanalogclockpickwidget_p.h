
#ifndef _HACANALOGCLOCKPICKWIDGETPRIVATE_H_
#define _HACANALOGCLOCKPICKWIDGETPRIVATE_H_

#include "hacanalogclockpickwidget.h"

class HacAnalogClockPickWidgetPrivate
{
public:
	HacAnalogClockPickWidgetPrivate();
    ~HacAnalogClockPickWidgetPrivate();

	HacAnalogClockPickWidget::Precision precision;
	QList<HacAnalogClockPickWidget::PickedItemData> pickedList;
	bool textVisible;
	bool picking;
	QTime pickingStart;
	QTime pickingEnd;

private:

};

#endif // _HACANALOGCLOCKPICKWIDGETPRIVATE_H_
