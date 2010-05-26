
#ifndef _CHOOSESETDATETIMEWIDGET_H_
#define _CHOOSESETDATETIMEWIDGET_H_

#include <hacsettings-config.h>
#include <QWidget>

namespace Ui {
    class ChooseSetDateTimeWidget;
}

class QListWidgetItem;

class HACSETTINGS_EXPORT ChooseSetDateTimeWidget : public QWidget {
    Q_OBJECT

public:
    ChooseSetDateTimeWidget(QWidget *parent = NULL);
    ~ChooseSetDateTimeWidget();

	enum ChooseSet {
		ChooseSetNone,
		ChooseSetDate,
		ChooseSetTime
	};

	ChooseSet choosed() const { return d_choosed; }

Q_SIGNALS:
	void choosed(ChooseSet);
	void choosedSetDate();
	void choosedSetTime();
	void returned();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_previousMenuButton_pressed();
	void on_setDateButton_pressed();
	void on_setTimeButton_pressed();

private:

private:
    Ui::ChooseSetDateTimeWidget *ui;
	ChooseSet d_choosed;
};


#endif // _CHOOSESETDATETIMEWIDGET_H_
