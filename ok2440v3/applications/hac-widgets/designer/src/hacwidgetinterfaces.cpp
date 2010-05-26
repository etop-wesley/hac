#include "hacwidgetinterfaces.h"
#include "hacanalogclockpickwidget.h"
#include "hacframe.h"
#include "haclabel.h"
#include "hactimelabel.h"
#include "haclightlabel.h"
#include "haclistnavigator.h"
#include "hacnumberpad.h"
#include "hacpushbutton.h"
#include "hactabwidget.h"
#include "hacscrollbar.h"
#include "hacscrollarea.h"
#include "hacspinbox.h"
#include "haclineedit.h"

#include <QtCore/QtPlugin>

HacAnalogClockPickWidgetInterface::HacAnalogClockPickWidgetInterface(QObject *parent)
:   CustomWidgetInterface(parent)
{
	m_isContainer = true;
    m_group = "HacWidgets";
    m_name = "HacAnalogClockPickWidget";
    m_include = "hacanalogclockpickwidget.h";
    m_domXml = 
        "<widget class=\"HacAnalogClockPickWidget\" name=\"frame\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>100</width>\n"
        "   <height>100</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QWidget *HacAnalogClockPickWidgetInterface::createWidget(QWidget *parent)
{
    return new HacAnalogClockPickWidget(parent);
}

HacFrameInterface::HacFrameInterface(QObject *parent)
:   CustomWidgetInterface(parent)
{
	m_isContainer = true;
    m_group = "HacWidgets";
    m_name = "HacFrame";
    m_include = "hacframe.h";
    m_domXml = 
        "<widget class=\"HacFrame\" name=\"frame\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>120</width>\n"
        "   <height>80</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QWidget *HacFrameInterface::createWidget(QWidget *parent)
{
    return new HacFrame(parent);
}

HacLabelInterface::HacLabelInterface(QObject *parent)
:   CustomWidgetInterface(parent)
{
	m_group = "HacWidgets";
    m_name = "HacLabel";
    m_include = "haclabel.h";
    m_domXml = 
        "<widget class=\"HacLabel\" name=\"label\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>50</width>\n"
        "   <height>50</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QWidget *HacLabelInterface::createWidget(QWidget *parent)
{
    return new HacLabel(parent);
}

HacTimeLabelInterface::HacTimeLabelInterface(QObject *parent)
:   CustomWidgetInterface(parent)
{
	m_group = "HacWidgets";
    m_name = "HacTimeLabel";
    m_include = "hactimelabel.h";
    m_domXml = 
        "<widget class=\"HacTimeLabel\" name=\"timeLabel\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>100</width>\n"
        "   <height>50</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QWidget *HacTimeLabelInterface::createWidget(QWidget *parent)
{
    return new HacTimeLabel(parent);
}

HacLightLabelInterface::HacLightLabelInterface(QObject *parent)
:   CustomWidgetInterface(parent)
{
	m_group = "HacWidgets";
    m_name = "HacLightLabel";
    m_include = "haclightlabel.h";
    m_domXml = 
        "<widget class=\"HacLightLabel\" name=\"lightLabel\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>100</width>\n"
        "   <height>100</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QWidget *HacLightLabelInterface::createWidget(QWidget *parent)
{
    return new HacLightLabel(parent);
}

HacListNavigatorInterface::HacListNavigatorInterface(QObject *parent)
:   CustomWidgetInterface(parent)
{
	m_group = "HacWidgets";
    m_name = "HacListNavigator";
    m_include = "haclistnavigator.h";
    m_domXml = 
        "<widget class=\"HacListNavigator\" name=\"listNavigator\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>200</width>\n"
        "   <height>50</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QWidget *HacListNavigatorInterface::createWidget(QWidget *parent)
{
    return new HacListNavigator(parent);
}

HacNumberPadInterface::HacNumberPadInterface(QObject *parent)
:   CustomWidgetInterface(parent)
{
	m_group = "HacWidgets";
    m_name = "HacNumberPad";
    m_include = "hacnumberpad.h";
    m_domXml = 
        "<widget class=\"HacNumberPad\" name=\"numPad\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>200</width>\n"
        "   <height>200</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QWidget *HacNumberPadInterface::createWidget(QWidget *parent)
{
    return new HacNumberPad(parent);
}

HacPushButtonInterface::HacPushButtonInterface(QObject *parent)
:   CustomWidgetInterface(parent)
{
	m_group = "HacWidgets";
    m_name = "HacPushButton";
    m_include = "hacpushbutton.h";
    m_domXml = 
        "<widget class=\"HacPushButton\" name=\"button\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>100</width>\n"
        "   <height>50</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QWidget *HacPushButtonInterface::createWidget(QWidget *parent)
{
    return new HacPushButton(parent);
}

HacTabWidgetInterface::HacTabWidgetInterface(QObject *parent)
:   CustomWidgetInterface(parent)
{
	m_isContainer = true;
	m_group = "HacWidgets";
    m_name = "HacTabWidget";
    m_include = "hactabwidget.h";
    m_domXml = 
        "<widget class=\"HacTabWidget\" name=\"tabWidget\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>200</width>\n"
        "   <height>200</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QWidget *HacTabWidgetInterface::createWidget(QWidget *parent)
{
    return new HacTabWidget(parent);
}

HacScrollBarInterface::HacScrollBarInterface(QObject *parent)
:   CustomWidgetInterface(parent)
{
	m_group = "HacWidgets";
    m_name = "HacScrollBar";
    m_include = "hacscrollbar.h";
    m_domXml = 
        "<widget class=\"HacScrollBar\" name=\"scrollBar\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>40</width>\n"
        "   <height>100</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QWidget *HacScrollBarInterface::createWidget(QWidget *parent)
{
    return new HacScrollBar(parent);
}

HacScrollAreaInterface::HacScrollAreaInterface(QObject *parent)
:   CustomWidgetInterface(parent)
{
	m_isContainer = true;
    m_group = "HacWidgets";
    m_name = "HacScrollArea";
    m_include = "hacscrollarea.h";
    m_domXml = 
        "<widget class=\"HacScrollArea\" name=\"scrollArea\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>100</width>\n"
        "   <height>100</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QWidget *HacScrollAreaInterface::createWidget(QWidget *parent)
{
    return new HacScrollArea(parent);
}

HacSpinBoxInterface::HacSpinBoxInterface(QObject *parent)
:   CustomWidgetInterface(parent)
{
	m_isContainer = false;
    m_group = "HacWidgets";
    m_name = "HacSpinBox";
    m_include = "hacspinbox.h";
    m_domXml = 
        "<widget class=\"HacSpinBox\" name=\"spinbox\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>100</width>\n"
        "   <height>100</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QWidget *HacSpinBoxInterface::createWidget(QWidget *parent)
{
    return new HacSpinBox(parent);
}

HacLineEditInterface::HacLineEditInterface(QObject *parent)
:   CustomWidgetInterface(parent)
{
	m_isContainer = false;
    m_group = "HacWidgets";
    m_name = "HacLineEdit";
    m_include = "haclineedit.h";
    m_domXml = 
        "<widget class=\"HacLineEdit\" name=\"lineEdit\">\n"
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

QWidget *HacLineEditInterface::createWidget(QWidget *parent)
{
    return new HacLineEdit(parent);
}

