#ifndef _STATUSBAR_H_
#define _STATUSBAR_H_

#include <QWidget>

namespace Ui {
    class StatusBar;
}

class StatusBar : public QWidget {
    Q_OBJECT

public:
    StatusBar(QWidget *parent = NULL, Qt::WindowFlags f = 0);
    ~StatusBar();

Q_SIGNALS:
	void homeClicked();
	void backClicked();
	void clockClicked();

public Q_SLOTS:

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:

private:

private:
    Ui::StatusBar *ui;
};

#endif // _STATUSBAR_H_
