#ifndef _HACWIDGET_H_
#define _HACWIDGET_H_

#include <QWidget>

class HacWidget : public QWidget {
	Q_OBJECT

public:
	explicit HacWidget(QWidget *parent = NULL, Qt::WindowFlags f = 0);
	~HacWidget();

	void setBackground();

Q_SIGNALS:

protected:
	void changeEvent(QEvent *);

private Q_SLOTS:

	private:
};

#endif //_HACWIDGET_H_
