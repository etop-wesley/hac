#include "hactabbar.h"
#include "hactabbar_p.h"

HacTabBar::HacTabBar(QWidget *parent)
: QTabBar(parent), d(new HacTabBarPrivate)
{
	d->expandingAllTabs = false;
}

HacTabBar::~HacTabBar()
{
    if (d != NULL) {
        delete d;
        d = NULL;
    }
}

bool HacTabBar::expandintAllTabs() const
{
	return d->expandingAllTabs;
}

void HacTabBar::setExpandintAllTabs(bool enable)
{
	if (enable != d->expandingAllTabs) {
		d->expandingAllTabs = enable;
		updateGeometry();
	}
}


QSize HacTabBar::tabSizeHint(int index) const
{
	if (d->expandingAllTabs && parentWidget() != NULL) {
		QSize size = QTabBar::tabSizeHint(index);
		if (!size.isEmpty() && count() != 0) {
			if (shape() == QTabBar::RoundedWest
				   || shape() == QTabBar::RoundedEast
				   || shape() == QTabBar::TriangularWest
				   || shape() == QTabBar::TriangularEast) { // It is vertical tabs
				size.setHeight(parentWidget()->height() / count());
			} else { // It is horizontal tabs
				size.setWidth(parentWidget()->width() / count());
			}
		}
		return size;
	} else {
        return QTabBar::tabSizeHint(index);
	}
}


/*
 * internal
 */
HacTabBarPrivate::HacTabBarPrivate()
{
}

/*
 * internal
 */
HacTabBarPrivate::~HacTabBarPrivate()
{
}
