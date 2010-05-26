#ifndef _HACSPINBOX_P_H_
#define _HACSPINBOX_P_H_

#include "hacspinbox.h"

class QLabel;
class QTimeLine;
class HacLineEdit;

class HacSpinBoxPrivate
{
public:
    HacSpinBoxPrivate();
    ~HacSpinBoxPrivate();

	HacSpinBox::ContentType contentType; 
    QStringList strings;
	QTimeLine *timeLine;
	HacLineEdit *lineEdit; // fixing QLineEdit touch crash bug
private:

};

#endif // _HACSPINBOX_P_H_
