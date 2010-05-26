#ifndef _MAINSTAGEPAGE_H_
#define _MAINSTAGEPAGE_H_

#include <QWidget>

namespace Ui {
    class MainStagePage;
}

class QListWidgetItem;

class MainStagePage : public QWidget {
    Q_OBJECT
public:
    MainStagePage(QWidget *parent = 0);
    ~MainStagePage();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_listWidget_itemClicked(QListWidgetItem *item);

private:
	void readSettings();
	void writeSettings();

private:
    Ui::MainStagePage *ui;
};

#endif // _MAINSTAGEPAGE_H_
