#ifndef _SWITCHSCHEDULEDELAYPICK_H_
#define _SWITCHSCHEDULEDELAYPICK_H_

#include <QDialog>
#include "switchscheduleitemdata.h"

namespace Ui {
    class SwitchScheduleDelayPick;
}

class SwitchScheduleDelayPick : public QDialog {
    Q_OBJECT

public:
    SwitchScheduleDelayPick(QWidget * parent = 0, Qt::WindowFlags f = 0);
    ~SwitchScheduleDelayPick();

	void setData(const SwitchScheduleDelayData &data);
	SwitchScheduleDelayData data() const;

public Q_SLOTS:
    void accept();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:

private:

private:
    Ui::SwitchScheduleDelayPick *ui;
	SwitchScheduleDelayData d_data;
};

#endif // _SWITCHSCHEDULEDELAYPICK_H_
