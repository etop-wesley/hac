#ifndef _HACLINEEDIT_H_
#define _HACLINEEDIT_H_

#include "hacwidgetglobal.h"
#include <QtGui/QLineEdit>

class HacLineEditPrivate;

class HACWIDGET_EXPORT HacLineEdit : public QLineEdit {
	Q_OBJECT

public:
	HacLineEdit(QWidget *parent = 0);
    HacLineEdit(const QString &contents, QWidget * parent = 0);
	~HacLineEdit();

Q_SIGNALS:

public Q_SLOTS:

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);

private Q_SLOTS:

private:

private:
	HacLineEditPrivate *d;
};

#endif // _HACLINEEDIT_H_
