#ifndef _SWITCHSCHEDULESET_H_
#define _SWITCHSCHEDULESET_H_

#include <QWidget>

namespace Ui {
    class SwitchScheduleSet;
}

class SwitchScheduleSet : public QWidget {
    Q_OBJECT
public:
    SwitchScheduleSet(QWidget *parent = 0);
    ~SwitchScheduleSet();

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
    Ui::SwitchScheduleSet *ui;
};

#endif // _SWITCHSCHEDULESET_H_
