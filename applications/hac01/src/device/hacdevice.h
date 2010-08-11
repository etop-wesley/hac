#ifndef _HACDEVICE_H_
#define _HACDEVICE_H_

#include <QObject>
#include "hacdevicemanager.h"

class HacDevice : public QObject {
    Q_OBJECT

public:
	enum DeviceType {
		Device_None = 0,
		Device_Switch = 1,
	};

    HacDevice(DeviceType type, HacDeviceManager *manager, QObject *parent = NULL);
    ~HacDevice();

    virtual DeviceType deviceType() const { return d_deviceType; }
    virtual void setDeviceType(DeviceType type) { d_deviceType = type; }

	virtual bool transmit(const QByteArray &);
	virtual QByteArray receive();
	
Q_SIGNALS:

public Q_SLOTS:

protected:

private Q_SLOTS:

private:

private:
	HacDeviceManager *d_manager;
	DeviceType d_deviceType;
};


#endif // _HACDEVICE_H_
