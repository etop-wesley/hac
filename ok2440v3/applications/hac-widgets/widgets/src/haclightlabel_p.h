#ifndef _HACLIGHTLABELPRIVATE_H_
#define _HACLIGHTLABELPRIVATE_H_

#include "haclightlabel.h"
#include <QImage>

class HacLightLabelPrivate
{
public:
    HacLightLabelPrivate();
    ~HacLightLabelPrivate();

    int	maximum;
    int	minimum;
    int	value;
	QImage *image;
    
private:

};

#endif // _HACLIGHTLABELPRIVATE_H_
