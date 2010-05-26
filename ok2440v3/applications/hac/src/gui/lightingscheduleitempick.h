#ifndef _LIGHTINGSCHEDULEITEMPICK_H_
#define _LIGHTINGSCHEDULEITEMPICK_H_

#include <QDialog>
#include "lightingscheduleitemdata.h"

namespace Ui {
    class LightingScheduleItemPick;
}

class LightingScheduleItemPick : public QDialog {
    Q_OBJECT

public:
    LightingScheduleItemPick(QWidget * parent = 0, Qt::WindowFlags f = 0);
    ~LightingScheduleItemPick();

	void setData(const LightingScheduleItemData &data);
	LightingScheduleItemData data() const;

public Q_SLOTS:
    void accept();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:

private:

private:
    Ui::LightingScheduleItemPick *ui;
	LightingScheduleItemData d_data;
};

#endif // _LIGHTINGSCHEDULEITEMPICK_H_
