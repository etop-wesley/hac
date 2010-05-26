#include "hacframe.h"
#include "hacframe_p.h"

HacFrame::HacFrame(QWidget *parent, Qt::WindowFlags f)
: QFrame(parent, f), d(new HacFramePrivate)
{
}

HacFrame::~HacFrame()
{
    if (d != NULL) {
        delete d;
        d = NULL;
    }
}

/*
 * internal
 */
HacFramePrivate::HacFramePrivate()
{
}

/*
 * internal
 */
HacFramePrivate::~HacFramePrivate()
{
}
