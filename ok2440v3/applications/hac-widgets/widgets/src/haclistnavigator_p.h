#ifndef _HACLISTNAVIGATORPRIVATE_H_
#define _HACLISTNAVIGATORPRIVATE_H_

#include "haclistnavigator.h"
#include <QListWidget>

class HacListNavigatorPrivate
{
public:
    HacListNavigatorPrivate();
    ~HacListNavigatorPrivate();

	HacListNavigator::Buttons buttons;
    QMap<HacListNavigator::Button, QWidget*> widgets;
    QListWidget *listWidget;

private:

};

#endif // _HACLISTNAVIGATORPRIVATE_H_
