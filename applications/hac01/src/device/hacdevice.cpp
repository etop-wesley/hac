//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#define _TTY_POSIX_
#include <qextserialport/qextserialport.h>
#include "hacdevice.h"

HacDevice::HacDevice(DeviceType type, HacDeviceManager *manager, QObject *parent)
: QObject(parent), d_deviceType(type), d_manager(manager)
{
    qDebug() << "HacDevice::HacDevice";
	//d_deviceType = Device_None;
}

HacDevice::~HacDevice()
{
    qDebug() << "HacDevice::~HacDevice";
}

bool HacDevice::transmit(const QByteArray &data)
{
	return d_manager->transmitData(data);
}

QByteArray HacDevice::receive()
{
	return d_manager->receiveData();
}


