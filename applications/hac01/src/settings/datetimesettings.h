#ifndef _DATETIMESETTINGS_H_
#define _DATETIMESETTINGS_H_

#include <QWidget>

namespace Ui {
    class DateTimeSettings;
}

class DateTimeSettings : public QWidget {
    Q_OBJECT
public:
    DateTimeSettings(QWidget *parent = 0);
    ~DateTimeSettings();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_downButton_pressed();
	void on_okButton_pressed();
	void on_cancelButton_pressed();

private:

private:
    Ui::DateTimeSettings *ui;
};

#endif // _DATETIMESETTINGS_H_
