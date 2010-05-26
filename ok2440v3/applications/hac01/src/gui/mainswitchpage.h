#ifndef _MAINSWITCHGPAGE_H_
#define _MAINSWITCHGPAGE_H_

#include <QWidget>

namespace Ui {
    class MainSwitchPage;
}

class MainSwitchPage : public QWidget {
    Q_OBJECT
public:
    MainSwitchPage(QWidget *parent = 0);
    ~MainSwitchPage();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_button_clicked(int);

private:

private:
    Ui::MainSwitchPage *ui;
};

#endif // _MAINSWITCHGPAGE_H_
