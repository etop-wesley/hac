#ifndef _HACTABBAR_H_
#define _HACTABBAR_H_

#include "hacwidgetglobal.h"
#include <QtGui/QTabBar>

class HacTabBarPrivate;

class HACWIDGET_EXPORT HacTabBar : public QTabBar {
	Q_OBJECT

	Q_PROPERTY(bool expandintAllTabs READ expandintAllTabs WRITE setExpandintAllTabs)

public:
	HacTabBar(QWidget *parent = 0);
	~HacTabBar();

	bool expandintAllTabs() const;
	void setExpandintAllTabs(bool enable);

protected:
    virtual QSize tabSizeHint(int index) const;

private:
	HacTabBarPrivate *d;
};

#endif // _HACTABBAR_H_
