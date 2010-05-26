#ifndef _CUSTOMWIDGETINTERFACE_H_
#define _CUSTOMWIDGETINTERFACE_H_

#include <QDesignerCustomWidgetInterface>

/*
 * Note: That the only part of the class definition 
 *          that is specific to this particular custom widget is the class name.
 */
class CustomWidgetInterface : public QObject, public QDesignerCustomWidgetInterface {
	/*
	 * The Q_OBJECT macro must appear in the private section of a class definition
	 * that declares its own signals and slots or that uses other services
	 * provided by Qt's meta-object system.
	 */
	Q_OBJECT

	/*
	 * since we are implementing an interface,
	 * we must ensure that it's made known to the meta object system
	 * using the Q_INTERFACES( ) macro. 
	 * This enables Qt Designer to use the qobject_cast( ) function 
	 * to query for supported interfaces using nothing but a QObject pointer.
	 */
	Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
	CustomWidgetInterface(QObject *parent = 0);

	virtual bool isContainer() const;
	virtual bool isInitialized() const;
	virtual QIcon icon() const;
	virtual QString domXml() const;
	virtual QString group() const;
	virtual QString includeFile() const;
	virtual QString name() const;
	virtual QString toolTip() const;
	virtual QString whatsThis() const;
	virtual QWidget *createWidget(QWidget *parent);
	virtual void initialize(QDesignerFormEditorInterface *core);

protected:
	bool m_isContainer;
	QString m_group;
	QString m_name;
	QString m_include;
	QString m_toolTip;
	QString m_whatsThis;
	QString m_domXml;
	QIcon m_icon;

private:
	bool m_initialized;
};

#endif // _CUSTOMWIDGETINTERFACE_H_
