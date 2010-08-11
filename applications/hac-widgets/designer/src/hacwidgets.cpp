#include "hacwidgets.h"
#include "hacwidgetinterfaces.h"

HacWidgets::HacWidgets(QObject *parent)
: QObject(parent)
{
	m_widgets.append(new HacListWidgetInterface(this));
	m_widgets.append(new HacDateTimeLabelInterface(this));
	m_widgets.append(new HacLedInterface(this));
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
