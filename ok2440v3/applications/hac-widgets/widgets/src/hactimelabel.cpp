
//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QPainter>
#include "hactimelabel.h"
#include "hactimelabel_p.h"

#define DEFAULT_ALIGNMENT (Qt::AlignCenter)
#define DEFAULT_DISPLAY_ROLE (HacTimeLabel::TimeOnly)
#define DEFAULT_REFRESH_INTERVAL (60*1000) //ms
#define DEFAULT_STRING_FORMAT ("hh:mm")
#define DEFAULT_DATE_FORMAT Qt::DefaultLocaleShortDate

HacTimeLabel::HacTimeLabel(QWidget *parent, Qt::WindowFlags f)
: HacLabel(parent, f), d(new HacTimeLabelPrivate)
{
    setAlignment(DEFAULT_ALIGNMENT);
    setDisplayRole(DEFAULT_DISPLAY_ROLE);
    setDateFormat(DEFAULT_DATE_FORMAT);
	setStringFormat(DEFAULT_STRING_FORMAT);
	setRefreshInterval(DEFAULT_REFRESH_INTERVAL);

    connect(&d->refreshTimer, SIGNAL(timeout( )), this, SLOT(OnRefreshTimerOut( )));

    refresh();
    start();
}

HacTimeLabel::~HacTimeLabel()
{
    if (d != NULL) {
        delete d;
        d = NULL;
    }
}

Qt::DateFormat HacTimeLabel::dateFormat() const
{ 
    return d->dateFormat;
}

void HacTimeLabel::setDateFormat(Qt::DateFormat format)
{
    if (format == d->dateFormat)
        return;

    d->dateFormat = format;
    refresh();
}

QString HacTimeLabel::stringFormat() const
{
    return d->stringFormat;
}

void HacTimeLabel::setStringFormat(const QString &format)
{
    if (format == d->stringFormat)
        return;

    d->stringFormat = format;
    refresh();
}

HacTimeLabel::DisplayRole HacTimeLabel::displayRole() const
{ 
    return d->displayRole;
}

void HacTimeLabel::setDisplayRole(DisplayRole role)
{
    if (role == d->displayRole)
        return;

    d->displayRole = role;
    refresh();
}

int HacTimeLabel::refreshInterval() const
{ 
    return d->refreshTimer.interval();
}

void HacTimeLabel::setRefreshInterval(int msec)
{ 
    d->refreshTimer.setInterval(msec);
}

void HacTimeLabel::start()
{
    d->refreshTimer.start();
}

void HacTimeLabel::stop()
{
    d->refreshTimer.stop();
}

void HacTimeLabel::refresh()
{ 
	QDateTime current(QDateTime::currentDateTime());
	QString currentText;
	switch (d->displayRole) {
	case DateTime:
		currentText = d->stringFormat.isEmpty() ? current.toString(d->dateFormat) : current.toString(d->stringFormat);
		break;
	case TimeOnly:
		currentText = d->stringFormat.isEmpty() ? current.time().toString(d->dateFormat) : current.time().toString(d->stringFormat);
		break;
	case DateOnly:
		currentText = d->stringFormat.isEmpty() ? current.date().toString(d->dateFormat) : current.date().toString(d->stringFormat);
		break;
	default:
		break;
	}

	setText(currentText);
    emit datetimeUpdated(current);

}

void HacTimeLabel::OnRefreshTimerOut()
{
	refresh();
}


/*
 * internal
 */
HacTimeLabelPrivate::HacTimeLabelPrivate()
{
}

/*
 * internal
 */
HacTimeLabelPrivate::~HacTimeLabelPrivate()
{
}

