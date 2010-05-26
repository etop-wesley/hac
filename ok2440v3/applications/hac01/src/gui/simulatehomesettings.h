#ifndef _SIMULATEHOMESETTINGS_H_
#define _AIRCONDITIONINGCONTROLPAGE_H_

#include <QWidget>
#include <QTime>

namespace Ui {
    class SimulateHomeSettings;
}


class SimulateHomeSettings : public QWidget {
    Q_OBJECT
public:
    SimulateHomeSettings(QWidget *parent = 0);
    ~SimulateHomeSettings();

	void setBeUsedInStage();


protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_upButton_pressed();
	void on_downButton_pressed();

private:

private:
    Ui::SimulateHomeSettings *ui;

	QTime d_lightOnTime;
	QTime d_lightOffTime;
};

#endif // _SIMULATEHOMESETTINGS_H_
