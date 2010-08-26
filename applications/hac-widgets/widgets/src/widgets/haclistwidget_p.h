#ifndef _HACLISTWIDGET_P_H_
#define _HACLISTWIDGET_P_H_

#include "haclistwidget.h"

class HacListWidgetPrivate
{
public:
	HacListWidgetPrivate();
	~HacListWidgetPrivate();

	bool backgroundTransparent;
	bool notIntersetedItems;
	QSize gridCount;

private:

};

#endif // _HACLISTWIDGET_P_H_
