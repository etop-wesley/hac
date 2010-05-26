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

private Q_SLOTS:

private:
	void readSettings();
	void writeSettings();

private:
    Ui::HacMainWindow *ui;
};

#endif // _HACMAINWINDOW_H
