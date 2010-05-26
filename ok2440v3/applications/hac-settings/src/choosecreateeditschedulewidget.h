
#ifndef _CHOOSECREATEEDITSCHEDULEWIDGET_H_
#define _CHOOSECREATEEDITSCHEDULEWIDGET_H_

#include <hacsettings-config.h>
#include <QWidget>

namespace Ui {
    class ChooseCreateEditScheduleWidget;
}

class HACSETTINGS_EXPORT ChooseCreateEditScheduleWidget : public QWidget {
    Q_OBJECT

public:
    ChooseCreateEditScheduleWidget(QWidget *parent = NULL);
    ~ChooseCreateEditScheduleWidget();

Q_SIGNALS:
	void back();
	void help();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_backButton_pressed();
	void on_helpButton_pressed();

private:

private:
    Ui::ChooseCreateEditScheduleWidget *ui;
};


#endif // _CHOOSECREATEEDITSCHEDULEWIDGET_H_
