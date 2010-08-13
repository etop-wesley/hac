#ifndef _HACLISTWIDGET_H_
#define _HACLISTWIDGET_H_

#include "hacwidgetsglobal.h"
#include <QtGui/QListWidget>

class HacListWidgetPrivate;

class HACWIDGET_EXPORT HacListWidget : public QListWidget {
	Q_OBJECT

	Q_PROPERTY(bool backgroundTransparent READ backgroundTransparent WRITE setBackgroundTransparent)
	Q_PROPERTY(bool notIntersetedItems READ notIntersetedItems WRITE setNotIntersetedItems)
	Q_PROPERTY(QSize gridCount READ gridCount WRITE setGridCount)

public:
	HacListWidget(QWidget *parent = NULL);
	~HacListWidget();

	bool backgroundTransparent() const;
	void setBackgroundTransparent(bool enable);

	bool notIntersetedItems() const;
	void setNotIntersetedItems(bool enable);

	QSize gridCount() const;
	void setGridCount(const QSize &count);

	QRect visualRect(const QModelIndex &index) const;

protected:
	void resizeEvent(QResizeEvent *event);

private:
	HacListWidgetPrivate *d;

};

#endif // _HACLISTWIDGET_H_
