#ifndef _HACSTATUSWIDGET_H_
#define _HACSTATUSWIDGET_H_

#include <QWidget>

namespace Ui {
    class HacStatusWidget;
}

class HacStatusWidget : public QWidget {
    Q_OBJECT
public:
    HacStatusWidget(QWidget *parent = NULL);
    ~HacStatusWidget();

Q_SIGNALS:
	void homeClicked();
	void backClicked();
	void clockClicked();

public Q_SLOTS:

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_homeButton_clicked();
	void on_backButton_clicked();
	void on_clockLabel_clicked();

private:

private:
    Ui::HacStatusWidget *ui;
};

#endif // _HACSTATUSWIDGET_H_
