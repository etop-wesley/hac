#ifndef _CURTAINSCONTROL_H_
#define _CURTAINSCONTROL_H_

#include <QWidget>

namespace Ui {
	class CurtainsControl;
}

class CurtainsControl : public QWidget {
	Q_OBJECT

public:
	CurtainsControl(QWidget *parent = NULL,  Qt::WindowFlags f = 0);
	~CurtainsControl();

public Q_SLOTS:

Q_SIGNALS:

protected:
	void changeEvent(QEvent *e);

private Q_SLOTS:

private:

private:
	Ui::CurtainsControl *ui;
};

#endif // _CURTAINSCONTROL_H_
