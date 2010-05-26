#ifndef _HACTIMELABEL_P_H_
#define _HACTIMELABEL_P_H_

#include <QColor>
#include <QTimer>
#include <QDateTime>
#include "hactimelabel.h"

class HacTimeLabelPrivate
{
public:
    HacTimeLabelPrivate();
    ~HacTimeLabelPrivate();

    Qt::DateFormat dateFormat;
    QString stringFormat;
    HacTimeLabel::DisplayRole displayRole;
    QTimer refreshTimer;

private:

};

#endif // _HACTIMELABEL_P_H_
