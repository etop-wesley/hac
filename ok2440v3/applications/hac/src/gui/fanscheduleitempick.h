#ifndef _FANSCHEDULEITEMPICK_H_
#define _FANSCHEDULEITEMPICK_H_

#include <QDialog>
#include "fanscheduleitemdata.h"

namespace Ui {
    class FanScheduleItemPick;
}

class FanScheduleItemPick : public QDialog {
    Q_OBJECT

public:
    FanScheduleItemPick(QWidget * parent = 0, Qt::WindowFlags f = 0);
    ~FanScheduleItemPick();

	void setData(const FanScheduleItemData &data);
	FanScheduleItemData data() const;

public Q_SLOTS:
    void accept();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:

private:

private:
    Ui::FanScheduleItemPick *ui;
	FanScheduleItemData d_data;
};

#endif // _FANSCHEDULEITEMPICK_H_
