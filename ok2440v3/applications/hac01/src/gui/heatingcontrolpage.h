#ifndef _HEATINGCONTROLPAGE_H_
#define _HEATINGCONTROLPAGE_H_

#include <QWidget>

namespace Ui {
    class HeatingControlPage;
}

class HeatingControlPage : public QWidget {
    Q_OBJECT
public:
    HeatingControlPage(QWidget *parent = 0);
    ~HeatingControlPage();

	void setBeUsedInStage();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_tempUpButton_pressed();
	void on_tempDownButton_pressed();

	void on_scheduleButton_pressed();

private:

private:
    Ui::HeatingControlPage *ui;
};

#endif // _HEATINGCONTROLPAGE_H_
