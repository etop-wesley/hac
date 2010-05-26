#include "hactabwidget.h"
#include "hactabwidget_p.h"
#include "hactabbar.h"

HacTabWidget::HacTabWidget(QWidget *parent)
: QTabWidget(parent), d(new HacTabWidgetPrivate)
{
	d->tabBar = new HacTabBar(this);
	d->tabBar->setExpandintAllTabs(true);
	setTabBar(d->tabBar);
}

HacTabWidget::~HacTabWidget()
{
    if (d->tabBar != NULL) {
        delete d->tabBar;
        d->tabBar = NULL;
    }
    if (d != NULL) {
        delete d;
        d = NULL;
    }
}

/*
 * internal
 */
HacTabWidgetPrivate::HacTabWidgetPrivate()
{
}

/*
 * internal
 */
HacTabWidgetPrivate::~HacTabWidgetPrivate()
{
}
