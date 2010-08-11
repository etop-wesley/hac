#ifndef _LIGHTINGSCONTROL_H_
#define _LIGHTINGSCONTROL_H_

#include <QWidget>

namespace Ui {
	class LightingsControl;
}

class LightingsControl : public QWidget {
	Q_OBJECT

public:
	LightingsControl(QWidget *parent = NULL,  Qt::WindowFlags f = 0);
	~LightingsControl();

public Q_SLOTS:

Q_SIGNALS:

protected:
	void changeEvent(QEvent *e);

private Q_SLOTS:
    void OnButtonClicked(const QString &);

private:

private:
	Ui::LightingsControl *ui;
};

#endif // _LIGHTINGSCONTROL_H_
