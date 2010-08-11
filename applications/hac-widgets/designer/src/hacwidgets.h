#ifndef _HACWIDGETS_H_
#define _HACWIDGETS_H_

#include <QtDesigner/QtDesigner>
#include <QtCore/qplugin.h>

class HacWidgets : public QObject, public QDesignerCustomWidgetCollectionInterface
{
	Q_OBJECT
	Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

public:
	explicit HacWidgets(QObject *parent = 0);

	virtual QList<QDesignerCustomWidgetInterface*> customWidgets() const;

private:
	QList<QDesignerCustomWidgetInterface*> m_widgets;
};

#endif // _HACWIDGETS_H_
