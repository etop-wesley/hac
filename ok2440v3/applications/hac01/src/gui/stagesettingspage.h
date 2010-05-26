#ifndef _STAGESETTINGSPAGE_H_
#define _STAGESETTINGSPAGE_H_

#include <QWidget>

namespace Ui {
    class StageSettingsPage;
}
#include <QTime>

class StageSettingsPage : public QWidget {
    Q_OBJECT
public:
    StageSettingsPage(QWidget *parent = 0);
    ~StageSettingsPage();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_acButton_pressed();
	void on_heatingButton_pressed();
	void on_lightButton_pressed();
	void on_switchButton_pressed();
//	void on_curtainsButton_pressed();

	void on_tempUpButton_pressed();
	void on_tempDownButton_pressed();
	void on_tempUpButton2_pressed();
	void on_tempDownButton2_pressed();

	void on_lightUpButton_pressed();
	void on_lightDownButton_pressed();


	void on_numUpButton_pressed();
	void on_numDownButton_pressed();
	void on_lightOnButton_pressed();
	void on_lightOffButton_pressed();


private:

private:
    Ui::StageSettingsPage *ui;

	QTime d_lightOnTime;
	QTime d_lightOffTime;

};

#endif // _STAGESETTINGSPAGE_H_
