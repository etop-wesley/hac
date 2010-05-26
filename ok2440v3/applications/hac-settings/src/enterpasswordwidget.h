
#ifndef _ENTERPASSWORDWIDGET_H_
#define _ENTERPASSWORDWIDGET_H_

#include <hacsettings-config.h>
#include <QWidget>

namespace Ui {
    class EnterPasswordWidget;
}

class HACSETTINGS_EXPORT EnterPasswordWidget : public QWidget {
    Q_OBJECT

public:
    EnterPasswordWidget(QWidget *parent = NULL);
    ~EnterPasswordWidget();

Q_SIGNALS:
	void cancelled();
	void done();
	void help();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_doneButton_pressed();
	void on_cancelButton_pressed();
	void on_helpButton_pressed();

private:

private:
    Ui::EnterPasswordWidget *ui;
};


#endif // _ENTERPASSWORDWIDGET_H_
