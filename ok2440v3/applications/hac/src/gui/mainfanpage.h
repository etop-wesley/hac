#ifndef _MAINFANPAGE_H_
#define _MAINFANPAGE_H_

#include <QWidget>

namespace Ui {
    class MainFanPage;
}

class MainFanPage : public QWidget {
    Q_OBJECT
public:
    MainFanPage(QWidget *parent = 0);
    ~MainFanPage();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_startButton_clicked();
	void on_stopButton_clicked();
	void on_scheduleButton_clicked();

private:

private:
    Ui::MainFanPage *ui;
};

#endif // _MAINFANPAGE_H_
