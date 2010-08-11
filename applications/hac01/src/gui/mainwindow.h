#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QWidget>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QWidget {
	Q_OBJECT

public:
	MainWindow(QWidget *parent = NULL,  Qt::WindowFlags f = 0);
	~MainWindow();

	QWidget * showWidget(const QString &name);

protected:
	void changeEvent(QEvent *e);

private Q_SLOTS:
    // start the slot name with "On"(not "on_") to avoid auto-connect!
    void OnHomeButtonClicked();
    void OnBackButtonClicked();

private:
	void readSettings();
	void writeSettings();

private:
	Ui::MainWindow *ui;
};

#endif // _MAINWINDOW_H_
