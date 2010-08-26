#ifndef _CALENDARCONTROL_H_
#define _CALENDARCONTROL_H_

#include <QWidget>

namespace Ui {
	class CalendarControl;
}

class CalendarControl : public QWidget {
	Q_OBJECT

public:
	CalendarControl(QWidget *parent = NULL,  Qt::WindowFlags f = 0);
	~CalendarControl();

public Q_SLOTS:

Q_SIGNALS:

protected:
	void changeEvent(QEvent *e);

private Q_SLOTS:
	void OnDaylyButtonClicked();
	void OnWeeklyButtonClicked();

private:

private:
	Ui::CalendarControl *ui;
};

#endif // _CALENDARCONTROL_H_
