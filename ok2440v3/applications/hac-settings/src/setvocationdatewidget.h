
#ifndef _SETVOCATIONDATEWIDGET_H_
#define _SETVOCATIONDATEWIDGET_H_

#include <hacsettings-config.h>
#include <QWidget>

namespace Ui {
    class SetVocationDateWidget;
}

class HACSETTINGS_EXPORT SetVocationDateWidget : public QWidget {
    Q_OBJECT

public:
    SetVocationDateWidget(QWidget *parent = NULL);
    ~SetVocationDateWidget();

Q_SIGNALS:
	void nexted();
	void cancelled();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_nextButton_pressed();
	void on_cancelButton_pressed();

private:

private:
    Ui::SetVocationDateWidget *ui;
};


#endif // _SETVOCATIONDATEWIDGET_H_
