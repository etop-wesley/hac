#ifndef _HACNUMBERPAD_H_
#define _HACNUMBERPAD_H_


#include "hacwidgetglobal.h"
#include <QWidget>

class HacNumberPadPrivate;

class HACWIDGET_EXPORT HacNumberPad : public QWidget
{
    Q_OBJECT

public:
    HacNumberPad(QWidget *parent = NULL);
    virtual ~HacNumberPad();

public Q_SLOTS:
    void animateClick(const QString &b, int msec = 100);

Q_SIGNALS:
    void numberClicked(int);
    void keyClicked(QString);
    void hashClicked();
    void asteriskClicked();

protected:

private Q_SLOTS:
    void OnButtonClicked(int);

private:

private:
    HacNumberPadPrivate *d;
};

#endif // _HacNUMBERPAD_H_
