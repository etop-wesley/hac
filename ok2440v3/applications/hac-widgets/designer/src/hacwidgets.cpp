#include "hacwidgets.h"
#include "hacwidgetinterfaces.h"

HacWidgets::HacWidgets(QObject *parent)
: QObject(parent)
{
    m_widgets.append(new HacAnalogClockPickWidgetInterface(this));
    m_widgets.append(new HacFrameInterface(this));
    m_widgets.append(new HacLabelInterface(this));
    m_widgets.append(new HacNumberPadInterface(this));
    m_widgets.append(new HacPushButtonInterface(this));
    m_widgets.append(new HacTimeLabelInterface(this));
    m_widgets.append(new HacLightLabelInterface(this));
    m_widgets.append(new HacListNavigatorInterface(this));
    m_widgets.append(new HacTabWidgetInterface(this));
    m_widgets.append(new HacScrollBarInterface(this));
    m_widgets.append(new HacScrollAreaInterface(this));
    m_widgets.append(new HacSpinBoxInterface(this));
    m_widgets.append(new HacLineEditInterface(this));
}

/* 
 *Returns a list of interfaces to the collection's custom widgets.
 */
QList<QDesignerCustomWidgetInterface*> HacWidgets::customWidgets( ) const
{
    return m_widgets;
}

/*
 * Export custom widget plugin to Qt Designer
 * Q_EXPORT_PLUGIN2(PluginName, ClassName)
 * This macro exports the plugin class ClassName for the plugin specified 
 * by PluginName. 
 * The value of PluginName should correspond 
 * to the TARGET specified in the plugin's project file.
 */
Q_EXPORT_PLUGIN2(hacwidgets, HacWidgets)
