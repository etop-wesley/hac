#ifndef _SWITCHSCHEDULEITEMPICK_H_
#define _SWITCHSCHEDULEITEMPICK_H_

#include <QDialog>
#include "switchscheduleitemdata.h"

namespace Ui {
    class SwitchScheduleItemPick;
}

class SwitchScheduleItemPick : public QDialog {
    Q_OBJECT

public:
    SwitchScheduleItemPick(QWidget * parent = 0, Qt::WindowFlags f = 0);
    ~SwitchScheduleItemPick();

	void setData(const SwitchScheduleItemData &data);
	SwitchScheduleItemData data() const;

public Q_SLOTS:
    void accept();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:

private:

private:
    Ui::SwitchScheduleItemPick *ui;
	SwitchScheduleItemData d_data;
};

#endif // _SWITCHSCHEDULEITEMPICK_H_
