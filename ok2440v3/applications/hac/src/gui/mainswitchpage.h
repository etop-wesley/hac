#ifndef _MAINSWITCHPAGE_H_
#define _MAINSWITCHPAGE_H_

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
	void on_startButton_clicked();
	void on_stopButton_clicked();
	void on_scheduleButton_clicked();

private:

private:
    Ui::MainSwitchPage *ui;
};

#endif // _MAINSWITCHPAGE_H_
