#ifndef _MAINSTAGEMODEPAGE_H_
#define _MAINSTAGEMODEPAGE_H_

#include <QWidget>

namespace Ui {
    class MainStageModePage;
}

class QListWidgetItem;

class MainStageModePage : public QWidget {
    Q_OBJECT
public:
    MainStageModePage(QWidget *parent = 0);
    ~MainStageModePage();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_listWidget_itemClicked(QListWidgetItem *item);

private:
	void readSettings();
	void writeSettings();

private:
    Ui::MainStageModePage *ui;
};

#endif // _MAINSTAGEMODEPAGE_H_
