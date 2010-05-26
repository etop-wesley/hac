#include "hacscrollarea.h"
#include "hacscrollarea_p.h"

HacScrollArea::HacScrollArea(QWidget *parent)
: QScrollArea(parent), d(new HacScrollAreaPrivate)
{
}

HacScrollArea::~HacScrollArea()
{
    if (d != NULL) {
        delete d;
        d = NULL;
    }
}

/*
 * internal
 */
HacScrollAreaPrivate::HacScrollAreaPrivate()
{
}

/*
 * internal
 */
HacScrollAreaPrivate::~HacScrollAreaPrivate()
{
}
