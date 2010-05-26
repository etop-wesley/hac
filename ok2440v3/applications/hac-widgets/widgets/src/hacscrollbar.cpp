#include "hacscrollbar.h"
#include "hacscrollbar_p.h"

HacScrollBar::HacScrollBar(QWidget *parent)
: QScrollBar(parent), d(new HacScrollBarPrivate)
{
}

HacScrollBar::HacScrollBar(Qt::Orientation orientation, QWidget *parent)
: QScrollBar(orientation, parent), d(new HacScrollBarPrivate)
{
}

HacScrollBar::~HacScrollBar()
{
    if (d != NULL) {
        delete d;
        d = NULL;
    }
}

/*
 * internal
 */
HacScrollBarPrivate::HacScrollBarPrivate()
{
}

/*
 * internal
 */
HacScrollBarPrivate::~HacScrollBarPrivate()
{
}
