#ifndef _HACMAINWINDOW_H
#define _HACMAINWINDOW_H

#include <QWidget>

namespace Ui {
    class HacMainWindow;
}

class HacMainWindow : public QWidget {
    Q_OBJECT
public:
    HacMainWindow(QWidget *parent = 0);
    ~HacMainWindow();

protected:
    void changeEvent(QEvent *e);
    void resizeEvent(QResizeEvent *e);

private Q_SLOTS:
	void on_statusWidget_homeClicked();
	void on_statusWidget_backClicked();
	void on_statusWidget_clockClicked();

private:
	void readSettings();
	void writeSettings();

private:
    Ui::HacMainWindow *ui;
};

#endif // _HACMAINWINDOW_H
