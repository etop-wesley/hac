#ifndef _LIGHTINGSCHEDULESET_H_
#define _LIGHTINGSCHEDULESET_H_

#include <QWidget>

namespace Ui {
    class LightingScheduleSet;
}

class LightingScheduleSet : public QWidget {
    Q_OBJECT
public:
    LightingScheduleSet(QWidget *parent = 0);
    ~LightingScheduleSet();

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
    Ui::LightingScheduleSet *ui;
};

#endif // _LIGHTINGSCHEDULESET_H_
