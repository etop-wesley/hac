#ifndef _AIRCONDITIONINGCONTROLPAGE_H_
#define _AIRCONDITIONINGCONTROLPAGE_H_

#include <QWidget>

namespace Ui {
    class AirConditioningControlPage;
}

class AirConditioningControlPage : public QWidget {
    Q_OBJECT
public:
    AirConditioningControlPage(QWidget *parent = 0);
    ~AirConditioningControlPage();

	void setBeUsedInStage();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_tempUpButton_pressed();
	void on_tempDownButton_pressed();

	void on_scheduleButton_pressed();

private:

private:
    Ui::AirConditioningControlPage *ui;
};

#endif // _AIRCONDITIONINGCONTROLPAGE_H_
