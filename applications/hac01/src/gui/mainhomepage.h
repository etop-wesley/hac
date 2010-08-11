#ifndef _MAINHOMEPAGE_H_
#define _MAINHOMEPAGE_H_

#include <QWidget>

namespace Ui {
    class MainHomePage;
}

class QListWidgetItem;
class MainWindow;

class MainHomePage : public QWidget {
    Q_OBJECT
public:
    MainHomePage(QWidget * parent = NULL, Qt::WindowFlags f = 0);
    ~MainHomePage();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
    // start the slot name with "On"(not "on_") to avoid auto-connect!
    void OnMenuListWidgetItemClicked(QListWidgetItem *item);
    void OnCalendarButtonClicked();
    void OnDateTimeLabelClicked();

private:
	void readSettings();
	void writeSettings();

private:
    Ui::MainHomePage *ui;
    MainWindow *mainWindow;
};

#endif // _MAINHOMEPAGE_H_
