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
	void on_button_clicked(int);


private:

private:
    Ui::MainLightingPage *ui;
};

#endif // _MAINLIGHTINGPAGE_H_
