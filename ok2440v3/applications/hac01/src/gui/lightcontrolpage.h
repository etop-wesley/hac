#ifndef _LIGHTCONTROLPAGE_H_
#define _LIGHTCONTROLPAGE_H_

#include <QWidget>

namespace Ui {
    class LightControlPage;
}

class LightControlPage : public QWidget {
    Q_OBJECT
public:
    LightControlPage(QWidget *parent = 0);
    ~LightControlPage();

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
    Ui::LightControlPage *ui;
};

#endif // _LIGHTCONTROLPAGE_H_
