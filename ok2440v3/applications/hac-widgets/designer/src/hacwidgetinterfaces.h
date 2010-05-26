#ifndef _HACWIDGETINTERFACES_H_
#define _HACWIDGETINTERFACES_H_

#include "customwidgetinterface.h"

class HacAnalogClockPickWidgetInterface: public CustomWidgetInterface 
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    HacAnalogClockPickWidgetInterface(QObject *parent);
    virtual QWidget *createWidget(QWidget *parent);
};


class HacFrameInterface: public CustomWidgetInterface 
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    HacFrameInterface(QObject *parent);
    virtual QWidget *createWidget(QWidget *parent);
};

class HacLabelInterface: public CustomWidgetInterface 
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    HacLabelInterface(QObject *parent);
    virtual QWidget *createWidget(QWidget *parent);
};

class HacLightLabelInterface: public CustomWidgetInterface 
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    HacLightLabelInterface(QObject *parent);
    virtual QWidget *createWidget(QWidget *parent);
};

class HacListNavigatorInterface: public CustomWidgetInterface 
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    HacListNavigatorInterface(QObject *parent);
    virtual QWidget *createWidget(QWidget *parent);
};

class HacNumberPadInterface: public CustomWidgetInterface 
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    HacNumberPadInterface(QObject *parent);
    virtual QWidget *createWidget(QWidget *parent);
};

class HacPushButtonInterface: public CustomWidgetInterface 
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    HacPushButtonInterface(QObject *parent);
    virtual QWidget *createWidget(QWidget *parent);
};

class HacTabWidgetInterface: public CustomWidgetInterface 
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    HacTabWidgetInterface(QObject *parent);
    virtual QWidget *createWidget(QWidget *parent);
};

class HacTimeLabelInterface: public CustomWidgetInterface 
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    HacTimeLabelInterface(QObject *parent);
    virtual QWidget *createWidget(QWidget *parent);
};

class HacScrollBarInterface: public CustomWidgetInterface 
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    HacScrollBarInterface(QObject *parent);
    virtual QWidget *createWidget(QWidget *parent);
};

class HacScrollAreaInterface: public CustomWidgetInterface 
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    HacScrollAreaInterface(QObject *parent);
    virtual QWidget *createWidget(QWidget *parent);
};

class HacSpinBoxInterface: public CustomWidgetInterface 
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    HacSpinBoxInterface(QObject *parent);
    virtual QWidget *createWidget(QWidget *parent);
};

class HacLineEditInterface: public CustomWidgetInterface 
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    HacLineEditInterface(QObject *parent);
    virtual QWidget *createWidget(QWidget *parent);
};

#endif // _HACWIDGETINTERFACES_H_
