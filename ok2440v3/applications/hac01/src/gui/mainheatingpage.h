#ifndef _MAINHEATINGPAGE_H_
#define _MAINHEATINGPAGE_H_

#include <QWidget>

namespace Ui {
    class MainHeatingPage;
}

class MainHeatingPage : public QWidget {
    Q_OBJECT
public:
    MainHeatingPage(QWidget *parent = 0);
    ~MainHeatingPage();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_button_clicked(int);

private:

private:
    Ui::MainHeatingPage *ui;
};

#endif // _MAINHEATINGPAGE_H_
