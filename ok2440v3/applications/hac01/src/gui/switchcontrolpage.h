#ifndef _SWITCHCONTROLPAGE_H_
#define _SWITCHCONTROLPAGE_H_

#include <QWidget>

namespace Ui {
    class SwitchControlPage;
}

class SwitchControlPage : public QWidget {
    Q_OBJECT
public:
    SwitchControlPage(QWidget *parent = 0);
    ~SwitchControlPage();

	void setBeUsedInStage();
	void setNum(int);

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_numUpButton_pressed();
	void on_numDownButton_pressed();
	void on_lightUpButton_pressed();
	void on_lightDownButton_pressed();
	void on_lightOnButton_pressed();
	void on_lightOffButton_pressed();


private:

private:
    Ui::SwitchControlPage *ui;
};

#endif // _SWITCHCONTROLPAGE_H_
