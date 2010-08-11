#ifndef _SWITCHESCONTROL_H_
#define _SWITCHESCONTROL_H_

#include <QWidget>

namespace Ui {
	class SwitchesControl;
}

class SwitchesControl : public QWidget {
	Q_OBJECT

public:
	SwitchesControl(QWidget *parent = NULL,  Qt::WindowFlags f = 0);
	~SwitchesControl();

public Q_SLOTS:

Q_SIGNALS:

protected:
	void changeEvent(QEvent *e);

private Q_SLOTS:
    void OnButtonClicked(const QString &);

private:

private:
	Ui::SwitchesControl *ui;
};

#endif // _SWITCHESCONTROL_H_
