#ifndef _HEATINGCONTROL_H_
#define _HEATINGCONTROL_H_

#include <QWidget>

namespace Ui {
	class HeatingControl;
}

class HeatingControl : public QWidget {
	Q_OBJECT

public:
	HeatingControl(QWidget *parent = NULL,  Qt::WindowFlags f = 0);
	~HeatingControl();

public Q_SLOTS:

Q_SIGNALS:

protected:
	void changeEvent(QEvent *e);

private Q_SLOTS:
    void OnButtonClicked(const QString &);

private:

private:
	Ui::HeatingControl *ui;
};

#endif // _HEATINGCONTROL_H_
