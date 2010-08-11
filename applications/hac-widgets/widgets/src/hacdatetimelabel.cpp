//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QDateTime>
#include "hacdatetimelabel.h"

#define DEFAULT_ALIGNMENT (Qt::AlignCenter)
#define DEFAULT_DISPLAY_ROLE (HacDateTimeLabel::DateTime)
#define DEFAULT_REFRESH_INTERVAL (60*1000) //ms
#define DEFAULT_STRING_FORMAT ("yyyy/M/d ddd hh:mm")
#define DEFAULT_DATE_FORMAT (Qt::LocaleDate)

/*
 * internal
 */
class HacDateTimeLabelPrivate {
public:
    HacDateTimeLabelPrivate(HacDateTimeLabel *pub) {}

    Qt::DateFormat dateFormat;
    QString stringFormat;
    HacDateTimeLabel::DisplayRole displayRole;
    QTimer refreshTimer;

private:

};


HacDateTimeLabel::HacDateTimeLabel(QWidget *parent, Qt::WindowFlags f)
: QLabel(parent, f), d(new HacDateTimeLabelPrivate(this))
{
    setAlignment(DEFAULT_ALIGNMENT);
    setDisplayRole(DEFAULT_DISPLAY_ROLE);
    setDateFormat(DEFAULT_DATE_FORMAT);
	setStringFormat(DEFAULT_STRING_FORMAT);
	setRefreshInterval(DEFAULT_REFRESH_INTERVAL);
	setContentsMargins(10, 5, 10, 5);
    connect(&d->refreshTimer, SIGNAL(timeout( )), this, SLOT(OnRefreshTimerOut( )));

    refresh();
    start();
}

HacDateTimeLabel::~HacDateTimeLabel()
{
    if (d != NULL) {
        delete d;
        d = NULL;
    }
}

Qt::DateFormat HacDateTimeLabel::dateFormat() const
{ 
    return d->dateFormat;
}

void HacDateTimeLabel::setDateFormat(Qt::DateFormat format)
{
    if (format == d->dateFormat)
        return;

    d->dateFormat = format;
    refresh();
}

QString HacDateTimeLabel::stringFormat() const
{
    return d->stringFormat;
}

void HacDateTimeLabel::setStringFormat(const QString &format)
{
    if (format == d->stringFormat)
        return;

    d->stringFormat = format;
    refresh();
}

HacDateTimeLabel::DisplayRole HacDateTimeLabel::displayRole() const
{ 
    return d->displayRole;
}

void HacDateTimeLabel::setDisplayRole(DisplayRole role)
{
    if (role == d->displayRole)
        return;

    d->displayRole = role;
    refresh();
}

int HacDateTimeLabel::refreshInterval() const
{ 
    return d->refreshTimer.interval();
}

void HacDateTimeLabel::setRefreshInterval(int msec)
{ 
    d->refreshTimer.setInterval(msec);
}

void HacDateTimeLabel::start()
{
    d->refreshTimer.start();
}

void HacDateTimeLabel::stop()
{
    d->refreshTimer.stop();
}

void HacDateTimeLabel::refresh()
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

void HacDateTimeLabel::OnRefreshTimerOut()
{
	refresh();
}
