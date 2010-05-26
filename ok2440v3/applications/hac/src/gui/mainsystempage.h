#ifndef _MAINSYSTEMPAGE_H_
#define _MAINSYSTEMPAGE_H_

#include <QWidget>

namespace Ui {
    class MainSystemPage;
}

class QListWidgetItem;

class MainSystemPage : public QWidget {
    Q_OBJECT

public:
    MainSystemPage(QWidget *parent = 0);
    ~MainSystemPage();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
	void readSettings();
	void writeSettings();

private:
    Ui::MainSystemPage *ui;
};

#endif // _MAINSYSTEMPAGE_H_
