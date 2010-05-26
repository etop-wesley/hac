#ifndef _MAINAIRCONDITIONINGPAGE_H_
#define _MAINAIRCONDITIONINGPAGE_H_

#include <QWidget>

namespace Ui {
    class MainAirConditioningPage;
}

class MainAirConditioningPage : public QWidget {
    Q_OBJECT
public:
    MainAirConditioningPage(QWidget *parent = 0);
    ~MainAirConditioningPage();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_button_clicked(int);

private:

private:
    Ui::MainAirConditioningPage *ui;
};

#endif // _MAINAIRCONDITIONINGPAGE_H_
