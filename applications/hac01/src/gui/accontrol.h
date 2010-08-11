#ifndef _ACCONTROL_H_
#define _ACCONTROL_H_

#include <QWidget>

namespace Ui {
	class AcControl;
}

class AcControl : public QWidget {
	Q_OBJECT

public:
	AcControl(QWidget *parent = NULL,  Qt::WindowFlags f = 0);
	~AcControl();

public Q_SLOTS:

Q_SIGNALS:

protected:
	void changeEvent(QEvent *e);

private Q_SLOTS:
    void OnButtonClicked(const QString &);

private:

private:
	Ui::AcControl *ui;
};

#endif // _ACCONTROL_H_
