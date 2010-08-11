#ifndef _HACWIDGETINTERFACES_H_
#define _HACWIDGETINTERFACES_H_

#include "customwidgetinterface.h"


class HacListWidgetInterface: public CustomWidgetInterface
{
	Q_OBJECT
	Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
	HacListWidgetInterface(QObject *parent);
	virtual QWidget *createWidget(QWidget *parent);
};

class HacDateTimeLabelInterface: public CustomWidgetInterface
{
	Q_OBJECT
	Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
	HacDateTimeLabelInterface(QObject *parent);
	virtual QWidget *createWidget(QWidget *parent);
};

class HacLedInterface: public CustomWidgetInterface
{
	Q_OBJECT
	Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
	HacLedInterface(QObject *parent);
	virtual QWidget *createWidget(QWidget *parent);
};

#endif // _HACWIDGETINTERFACES_H_
