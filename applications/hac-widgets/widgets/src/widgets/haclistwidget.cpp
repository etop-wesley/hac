//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QMouseEvent>
#include "haclistwidget.h"
#include "haclistwidget_p.h"

HacListWidget::HacListWidget(QWidget *parent)
: QListWidget(parent), d(new HacListWidgetPrivate)
{
	d->backgroundTransparent = false;
	d->notIntersetedItems = true;
	d->gridCount = QSize();
}

HacListWidget::~HacListWidget()
{
	if (d != NULL) {
		delete d;
		d = NULL;
	}
}

/*!
	\property HacListWidget::backgroundTransparent
	\brief whether the view's background is transparent.

	This property holds whether the view's background is transparent.
	if true, both the view and viewport is transparent.

	By default, this property is false.
*/
bool HacListWidget::backgroundTransparent() const
{
	return d->backgroundTransparent;
}

void HacListWidget::setBackgroundTransparent(bool enable)
{
	if (enable != d->backgroundTransparent) {
		d->backgroundTransparent = enable;
		setAutoFillBackground(!d->backgroundTransparent);
		viewport()->setAutoFillBackground(!d->backgroundTransparent);
	}
}

/*!
	\property HacListWidget::notIntersetedItems
	\brief whether the items interseted with view border should be showed.

	This property holds whether the items those interseted with
	the view port border should be showed.
	if true, only the items entirely inside the view will be showed.

	By default, this property is true.
*/
bool HacListWidget::notIntersetedItems() const
{
	return d->notIntersetedItems;
}

void HacListWidget::setNotIntersetedItems(bool enable)
{
	if (enable != d->notIntersetedItems) {
		d->notIntersetedItems = enable;
		viewport()->update();
	}
}


/*!
	\property HacListWidget::gridCount
	\brief the grid layout count in horizontal and vertical direction.

	By default, this property is true.
*/
QSize HacListWidget::gridCount() const
{
	return d->gridCount;
}

void HacListWidget::setGridCount(const QSize &count)
{
	if (count != d->gridCount) {
		d->gridCount = count;
		viewport()->update();
	}
}

void HacListWidget::resizeEvent(QResizeEvent *event)
{
	QListWidget::resizeEvent(event);
	if (!d->gridCount.isEmpty())
		setGridSize(QSize(size().width() / d->gridCount.width(), size().height() / d->gridCount.height()));
}

QRect HacListWidget::visualRect(const QModelIndex &index) const
{
	QRect rect = QListWidget::visualRect(index);
	if (d->notIntersetedItems && !viewport()->rect().adjusted(-1, -1, 1, 1).contains(rect, true))
		return QRect();
	return rect;
}



/*
 * internal
 */
HacListWidgetPrivate::HacListWidgetPrivate()
{
}

/*
 * internal
 */
HacListWidgetPrivate::~HacListWidgetPrivate()
{
}
