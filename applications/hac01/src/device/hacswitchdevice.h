#ifndef _HACSWITCHDEVICE_H_
#define _HACSWITCHDEVICE_H_

#include "hacdevice.h"

class HacSwitchDevice : public HacDevice {
    Q_OBJECT

public:
    HacSwitchDevice(HacDeviceManager *manager, QObject *parent = NULL);
    ~HacSwitchDevice();

	bool switchControl(int, bool);
	bool switchControl(const QList<int> &, bool);

Q_SIGNALS:

public Q_SLOTS:

protected:

private Q_SLOTS:

private:

private:

};


#endif // _HACSWITCHDEVICE_H_
