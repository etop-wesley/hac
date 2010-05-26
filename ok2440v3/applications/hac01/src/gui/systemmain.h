#ifndef _SYSTEMMAIN_H_
#define _SYSTEMMAIN_H_

#include <QWidget>

namespace Ui {
    class SystemMain;
}

class QListWidgetItem;

class SystemMain : public QWidget {
    Q_OBJECT
public:
    SystemMain(QWidget *parent = 0);
    ~SystemMain();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_listWidget_itemClicked(QListWidgetItem *item);

private:

private:
    Ui::SystemMain *ui;
};

#endif // _SYSTEMMAIN_H_
