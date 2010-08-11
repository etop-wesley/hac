#include "hacwidgetinterfaces.h"
#include "haclistwidget.h"
#include "hacdatetimelabel.h"
#include "hacled.h"

#include <QtCore/QtPlugin>


HacListWidgetInterface::HacListWidgetInterface(QObject *parent)
:   CustomWidgetInterface(parent)
{
	m_isContainer = false;
	m_group = "HacWidgets";
	m_name = "HacListWidget";
	m_include = "haclistwidget.h";
	m_domXml = "<widget class=\"HacListWidget\" name=\"listWidget\">\n"
			   " <property name=\"geometry\">\n"
			   "  <rect>\n"
			   "   <x>0</x>\n"
			   "   <y>0</y>\n"
			   "   <width>100</width>\n"
			   "   <height>40</height>\n"
			   "  </rect>\n"
			   " </property>\n"
			   "</widget>\n";
}

QWidget *HacListWidgetInterface::createWidget(QWidget *parent)
{
	return new HacListWidget(parent);
}

HacDateTimeLabelInterface::HacDateTimeLabelInterface(QObject *parent)
:   CustomWidgetInterface(parent)
{
	m_isContainer = false;
	m_group = "HacWidgets";
	m_name = "HacDateTimeLabel";
	m_include = "hacdatetimelabel.h";
	m_domXml = "<widget class=\"HacDateTimeLabel\" name=\"dateTimeLabel\">\n"
			   " <property name=\"geometry\">\n"
			   "  <rect>\n"
			   "   <x>0</x>\n"
			   "   <y>0</y>\n"
			   "   <width>100</width>\n"
			   "   <height>40</height>\n"
			   "  </rect>\n"
			   " </property>\n"
			   "</widget>\n";
}

QWidget *HacDateTimeLabelInterface::createWidget(QWidget *parent)
{
	return new HacDateTimeLabel(parent);
}

HacLedInterface::HacLedInterface(QObject *parent)
:   CustomWidgetInterface(parent)
{
	m_isContainer = false;
	m_group = "HacWidgets";
	m_name = "HacLed";
	m_include = "hacled.h";
	m_domXml = "<widget class=\"HacLed\" name=\"led\">\n"
			   " <property name=\"geometry\">\n"
			   "  <rect>\n"
			   "   <x>0</x>\n"
			   "   <y>0</y>\n"
			   "   <width>40</width>\n"
			   "   <height>40</height>\n"
			   "  </rect>\n"
			   " </property>\n"
			   "</widget>\n";
}

QWidget *HacLedInterface::createWidget(QWidget *parent)
{
	return new HacLed(parent);
}


