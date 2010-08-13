#ifndef _HACDATETIMELABEL_H_
#define _HACDATETIMELABEL_H_

#include "hacwidgetsglobal.h"
#include <QLabel>

class HacDateTimeLabelPrivate;

class HACWIDGET_EXPORT HacDateTimeLabel : public QLabel
{
    Q_OBJECT

    Q_ENUMS(DisplayRole)
    Q_PROPERTY(DisplayRole displayRole READ displayRole WRITE setDisplayRole)
    Q_PROPERTY(QString stringFormat READ stringFormat WRITE setStringFormat)
    Q_PROPERTY(Qt::DateFormat dateFormat READ dateFormat WRITE setDateFormat)
    Q_PROPERTY(int refreshInterval READ refreshInterval WRITE setRefreshInterval)

public:
    enum DisplayRole {
        DateTime = 0,
        TimeOnly,
        DateOnly
    };

    explicit HacDateTimeLabel(QWidget *parent = NULL, Qt::WindowFlags f = 0);
    ~HacDateTimeLabel();

    Qt::DateFormat dateFormat() const;
    void setDateFormat(Qt::DateFormat);

	QString stringFormat() const;
	void setStringFormat(const QString &);

    DisplayRole displayRole() const;
    void setDisplayRole(DisplayRole);

    int refreshInterval() const;
    void setRefreshInterval(int);

    void refresh();
    
Q_SIGNALS:
    void datetimeUpdated(const QDateTime &);

public Q_SLOTS:
    void start();
    void stop();

private Q_SLOTS:
    void OnRefreshTimerOut();

protected:

private:
    HacDateTimeLabelPrivate *d;
};

#endif // _HACDATETIMELABEL_H_
