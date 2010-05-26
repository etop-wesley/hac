#ifndef _FANSCHEDULESET_H_
#define _FANSCHEDULESET_H_

#include <QWidget>

namespace Ui {
    class FanScheduleSet;
}

class FanScheduleSet : public QWidget {
    Q_OBJECT
public:
    FanScheduleSet(QWidget *parent = 0);
    ~FanScheduleSet();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_addButton_clicked();
	void on_delButton_clicked();
	void on_editButton_clicked();
	void on_okButton_clicked();
	void on_cancelButton_clicked();

private:

private:
    Ui::FanScheduleSet *ui;
};

#endif // _FANSCHEDULESET_H_
