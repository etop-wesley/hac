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

	QWidget * showPage(const QString &name);

protected:
	void changeEvent(QEvent *);

private Q_SLOTS:
    // start the slot name with "On"(not "on_") to avoid auto-connect!
    void OnHomeButtonClicked();
    void OnBackButtonClicked();

    void OnStackWidgetCurrentChanged(int);
    void OnStackWidgetWidgetRemoved(int);

private:
	void readSettings();
	void writeSettings();

private:
	Ui::MainWindow *ui;
};

#endif // _MAINWINDOW_H_
