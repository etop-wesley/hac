#ifndef _HOMEPAGE_H_
#define _HOMEPAGE_H_

#include <QWidget>

namespace Ui {
    class HomePage;
}

class QListWidgetItem;

class HomePage : public QWidget {
    Q_OBJECT
public:
    HomePage(QWidget * parent = NULL, Qt::WindowFlags f = 0);
    ~HomePage();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
    void OnMenuListWidgetItemClicked(QListWidgetItem *item);
    void OnCalendarButtonClicked();

private:
	void readSettings();
	void writeSettings();

private:
    Ui::HomePage *ui;
};

#endif // _HOMEPAGE_H_
