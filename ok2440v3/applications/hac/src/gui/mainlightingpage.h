#ifndef _MAINLIGHTINGPAGE_H_
#define _MAINLIGHTINGPAGE_H_

#include <QWidget>

namespace Ui {
    class MainLightingPage;
}

class MainLightingPage : public QWidget {
    Q_OBJECT
public:
    MainLightingPage(QWidget *parent = 0);
    ~MainLightingPage();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_startButton_clicked();
	void on_stopButton_clicked();
	void on_scheduleButton_clicked();
	void on_stageButton_clicked();

private:

private:
    Ui::MainLightingPage *ui;
};

#endif // _MAINLIGHTINGPAGE_H_
