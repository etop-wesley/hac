#ifndef _PASSWORDQUERYDIALOG_H_
#define _PASSWORDQUERYDIALOG_H_

#include <QDialog>
#include "fanscheduleitemdata.h"

namespace Ui {
    class PasswordQueryDialog;
}

class PasswordQueryDialog : public QDialog {
    Q_OBJECT

public:
    PasswordQueryDialog(QWidget * parent = 0, Qt::WindowFlags f = 0);
    ~PasswordQueryDialog();

	QString password() const;

public Q_SLOTS:

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_numpad_keyClicked(QString);

private:

private:
    Ui::PasswordQueryDialog *ui;
};

#endif // _PASSWORDQUERYDIALOG_H_
