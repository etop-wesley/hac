#ifndef _HACTIMELABEL_H_
#define _HACTIMELABEL_H_

#include "hacwidgetglobal.h"
#include <QLabel>
#include <QColor>
#include <QTimer>
#include <QDateTime>
#include "haclabel.h"

class HacTimeLabelPrivate;

class HACWIDGET_EXPORT HacTimeLabel : public HacLabel
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

    explicit HacTimeLabel(QWidget *parent = NULL, Qt::WindowFlags f = 0);
    ~HacTimeLabel();

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
    HacTimeLabelPrivate *d;
};

#endif // _HACTIMELABEL_H_
