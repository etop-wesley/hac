#ifndef _MAINHOMEPAGE_H_
#define _MAINHOMEPAGE_H_

#include <QWidget>

namespace Ui {
    class MainHomePage;
}

class QListWidgetItem;

class MainHomePage : public QWidget {
    Q_OBJECT
public:
    MainHomePage(QWidget *parent = 0);
    ~MainHomePage();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_listWidget_itemClicked(QListWidgetItem *item);

private:
	void readSettings();
	void writeSettings();

private:
    Ui::MainHomePage *ui;
};

#endif // _MAINHOMEPAGE_H_
