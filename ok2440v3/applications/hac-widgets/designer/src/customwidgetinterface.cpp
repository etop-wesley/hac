#include "customwidgetinterface.h"

#include <QtCore/QtPlugin>

CustomWidgetInterface::CustomWidgetInterface(QObject *parent)
: QObject(parent),
	m_initialized(false),
	m_isContainer(false),
	m_name(""),
	m_include(""),
	m_toolTip(""),
	m_whatsThis(""),
	m_domXml(""),
	m_icon(QIcon())
{
}

/*
 * Initializes the widget for use with the specified formEditor interface.
 * Sets up extensions and other features for custom widgets.
 * Custom container extensions (see QDesignerContainerExtension)
 * and task menu extensions (see QDesignerTaskMenuExtension)
 * should be set up in this function.
 */
void CustomWidgetInterface::initialize(QDesignerFormEditorInterface *formEditor)
{
	Q_UNUSED(formEditor);
	if (m_initialized)
		return;

	// Add extension registrations, etc. here

	m_initialized = true;
}

/*
 * Returns true if the widget has been initialized, otherwise returns false.
 * Reimplementations usually check whether the initialize( ) function
 * has been called and return the result of this test.
 */

bool CustomWidgetInterface::isInitialized() const
{
	return m_initialized;
}

/*
 * Returns a new instance of the custom widget, with the given parent.
 * the default implemention return Null.
 */
QWidget * CustomWidgetInterface::createWidget(QWidget *parent)
{
	Q_UNUSED(parent)
	return NULL;
}

/*
 * Returns the class name of the custom widget supplied by the interface.
 * The name returned must be identical to the class name 
 * used for the custom widget.
 */
QString CustomWidgetInterface::name() const
{
	return m_name;
}

/*
 * Returns the name of the group to which the custom widget belongs.
 */
QString CustomWidgetInterface::group() const
{
	return m_group;
}

/*
 * Returns the icon used to represent the custom widget in Qt Designer's widget box.
 */
QIcon CustomWidgetInterface::icon() const
{
	return m_icon;
}

/*
 * Returns a short description of the widget that can be used 
 * by Qt Designer in a tool tip.
 */
QString CustomWidgetInterface::toolTip() const
{
	return m_toolTip;
}

/*
 * Returns a description of the widget that can be used
 * by Qt Designer in "What's This?" help for the widget.
 */

QString CustomWidgetInterface::whatsThis() const
{
	return m_whatsThis;
}

/*
 * True if the widget will be used to hold child widgets; otherwise false.
 */
bool CustomWidgetInterface::isContainer() const
{
	return m_isContainer;
}

/*
 * Returns the XML that is used to describe the custom widget's properties to Qt Designer.
 */
QString CustomWidgetInterface::domXml() const
{
	return m_domXml;
}

/*
 * Returns the path to the include file that uic uses when creating code for the custom widget.
 * The header file that must be included in applications that use this widget. 
 * This information is stored in .ui files and will be used by uic 
 * to create a suitable #includes statement in the code it generates
 * for the form containing the custom widget.
 */
QString CustomWidgetInterface::includeFile() const
{
	return m_include;
}

