#include "hacpushbutton.h"
#include "hacpushbutton_p.h"

HacPushButton::HacPushButton(QWidget *parent)
: QPushButton(parent), d(new HacPushButtonPrivate)
{
}

HacPushButton::HacPushButton(const QString &text, QWidget * parent)
: QPushButton(text, parent), d(new HacPushButtonPrivate)
{
}

HacPushButton::HacPushButton(const QIcon &icon, const QString &text, QWidget *parent)
: QPushButton(icon, text, parent), d(new HacPushButtonPrivate)
{
}


HacPushButton::~HacPushButton()
{
    if (d != NULL) {
        delete d;
        d = NULL;
    }
}

/*
 * internal
 */
HacPushButtonPrivate::HacPushButtonPrivate()
{
}

/*
 * internal
 */
HacPushButtonPrivate::~HacPushButtonPrivate()
{
}
