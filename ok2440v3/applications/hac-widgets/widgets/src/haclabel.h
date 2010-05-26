#ifndef _HACLABEL_H_
#define _HACLABEL_H_

#include "hacwidgetglobal.h"
#include <QtGui/QLabel>

class HacLabelPrivate;

class HACWIDGET_EXPORT HacLabel : public QLabel {
	Q_OBJECT

	Q_PROPERTY(bool clickable READ isClickable WRITE setClickable)

public:
	HacLabel(QWidget * parent = 0, Qt::WindowFlags f =0);
	HacLabel(const QString & text, QWidget *parent = 0, Qt::WindowFlags f = 0);
	~HacLabel();

	bool isClickable() const;
	void setClickable(bool clickable);

Q_SIGNALS:
	void clicked();
	void pressed();
	void released();
	void doubleClicked();

	void mouseOver();
	void mouseOut();

public Q_SLOTS:

protected:
    void mouseDoubleClickEvent ( QMouseEvent * e );
    void mousePressEvent( QMouseEvent *e);
    void mouseReleaseEvent( QMouseEvent *e);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    bool hitLabel(const QPoint &p);

    //void keyPressEvent(QKeyEvent *e);
    //void keyReleaseEvent(QKeyEvent *e);

private Q_SLOTS:

private:

private:
	HacLabelPrivate *d;
};

#endif // _HACLABEL_H_
