#ifndef _STAGECONTROL_H_
#define _STAGECONTROL_H_

#include <QWidget>

namespace Ui {
	class StageControl;
}

class StageControl : public QWidget {
	Q_OBJECT

public:
	StageControl(QWidget *parent = NULL,  Qt::WindowFlags f = 0);
	~StageControl();

public Q_SLOTS:

Q_SIGNALS:

protected:
	void changeEvent(QEvent *e);

private Q_SLOTS:

private:

private:
	Ui::StageControl *ui;
};

#endif // _STAGECONTROL_H_
