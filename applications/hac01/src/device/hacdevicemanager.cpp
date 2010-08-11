//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#define _TTY_POSIX_
#include <qextserialport/qextserialport.h>
#include "hacdevicemanager.h"
#include "hacswitchdevice.h"
#include "hachelp.h"

#define SERIAL_PORT "/dev/ttySAC1"

HacDeviceManager::HacDeviceManager(QObject *parent)
: QObject(parent)
{
    qDebug() << "HacDeviceManager::HacDeviceManager";
	d_port = new QextSerialPort(SERIAL_PORT);
	d_port->setBaudRate(BAUD4800);   
	d_port->setFlowControl(FLOW_OFF);
	d_port->setParity(PAR_NONE);
	d_port->setDataBits(DATA_8);
	d_port->setStopBits(STOP_1);  
	d_port->setTimeout(1, 10);
}

HacDeviceManager::~HacDeviceManager()
{
    qDebug() << "HacDeviceManager::~HacDeviceManager";
	release();
}

bool HacDeviceManager::init()
{
	d_port->open(QIODevice::ReadWrite);
	qDebug("is open: %d", d_port->isOpen());
	return d_port->isOpen();
}

void HacDeviceManager::release()
{
	qDeleteAll(d_devices.begin(), d_devices.end());
	d_devices.clear();

	d_port->close();
	qDebug("is open: %d", d_port->isOpen());
}

bool HacDeviceManager::transmitData(const QByteArray &data)
{
    qDebug() << "HacDeviceManager::transmitData" << data.toHex();
	int i = d_port->write(data);
	qDebug("trasmitted : %d", i);
}

QByteArray HacDeviceManager::receiveData()
{
	qDebug() << "HacDeviceManager::receiveData";
	if (d_port->bytesAvailable() > 0)
		return d_port->read(1024);
	return QByteArray();
}

int HacDeviceManager::searchDevices()
{
	int retry = 3;
	bool found = false;
	while (retry --) {
		QByteArray data(8, 0);
		data[0] = 0x00;
		data[1] = 0x03;
		data[2] = 0x00;
		data[3] = 0x00;
		data[4] = 0x00;
		data[5] = 32;
		crc.crc_16bit=0xffff;
		calccrc(data[0]);
		calccrc(data[1]);
		calccrc(data[2]);
		calccrc(data[3]);
		calccrc(data[4]);
		calccrc(data[5]);
		data[6] = crc.crc_8bit[0];
		data[7] = crc.crc_8bit[1];
		transmitData(data);
		data = receiveData();
		qDebug() << data.toHex();
		if (data.at(0)== 0x00 && data.at(1) == 0x03 &&data.at(2)== 32
			&& data.at(3) == 0x0E && data.at(4) == 0xAA && data.at(5) == 0x11 && data.at(6) == 0xA0) {
			found = true;
			break;
		}
	}

	if (found) {
		d_devices.append(new HacSwitchDevice(this, this));
#ifdef HAC_SWITCH_TEST
		for (int i = 0; i < 18; i++) {
			HacSwitchDevice *swtDev = qobject_cast<HacSwitchDevice *>(d_devices.at(0));
			swtDev->switchControl(i, true);
			HacHelp::MSleep(100);
		}

		for (int i = 0; i < 18; i++) {
			HacSwitchDevice *swtDev = qobject_cast<HacSwitchDevice *>(d_devices.at(0));
			swtDev->switchControl(i, false);
			HacHelp::MSleep(100);
		}
#endif
	}
}




/*==============================================*/

union crc_buf_t crc;

void calccrc(unsigned char crcbuf)				//CRC–£—È¬Îº∆À„      
{
	unsigned char z1,TT;
	//crc.crc_8bit[1]=(crc.crc_8bit[1]^ crcbuf); 
	crc.crc_16bit=(crc.crc_16bit^ crcbuf);
	for (z1=0;z1<8;z1++) {
		//TT=crc.crc_8bit[1]; 
		TT=crc.crc_16bit&1;
		crc.crc_16bit=crc.crc_16bit>>1;
		crc.crc_16bit=crc.crc_16bit&0x7fff;
		if (TT&1) {
			crc.crc_16bit=crc.crc_16bit^0xa001;
			crc.crc_16bit=crc.crc_16bit&0xffff;
		}
		//crc.crc_16bit=crc.crc_16bit&0xffff;        
	}
}






