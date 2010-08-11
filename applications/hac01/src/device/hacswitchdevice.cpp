//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "hacswitchdevice.h"

HacSwitchDevice::HacSwitchDevice(HacDeviceManager *manager, QObject *parent)
: HacDevice(HacDevice::Device_Switch, manager, parent)
{
    qDebug() << "HacSwitchDevice::HacSwitchDevice";
}

HacSwitchDevice::~HacSwitchDevice()
{
    qDebug() << "HacSwitchDevice::~HacSwitchDevice";
}

bool HacSwitchDevice::switchControl(int index, bool on)
{
    qDebug() << "HacSwitchDevice::switchControl" << index << on;
	QByteArray data(8, 0);
	data[0] = 0x00;
	data[1] = 0x06;
	data[2] = 0x00;
	data[3] = 9 + index; // FIXME
	data[4] = 0x00;
	data[5] = on ? 0x01 : 0x00;
    crc.crc_16bit=0xffff;
	calccrc(data[0]);
	calccrc(data[1]);
	calccrc(data[2]);
	calccrc(data[3]);
	calccrc(data[4]);
	calccrc(data[5]);
	data[6] = crc.crc_8bit[0];
	data[7] = crc.crc_8bit[1];
	transmit(data);

	//data = receive();
	// qDebug() << data.toHex();
}

bool HacSwitchDevice::switchControl(const QList<int> &, bool)
{

}


