#ifndef _HACDEVICEMANAGER_H_
#define _HACDEVICEMANAGER_H_

#include <QObject>

class HacDevice;
class QextSerialPort;

class HacDeviceManager : public QObject {
    Q_OBJECT

public:
    HacDeviceManager(QObject *parent = NULL);
    ~HacDeviceManager();

	bool init();
	void release();

	int searchDevices();
	QList<HacDevice *> allDevices() const { return d_devices; }



    bool transmitData(const QByteArray &);
	QByteArray receiveData();

Q_SIGNALS:

public Q_SLOTS:

protected:

private Q_SLOTS:

private:

private:
	QextSerialPort *d_port;
	QList<HacDevice *> d_devices;
};



union crc_buf_t {
	unsigned int  crc_16bit ;
	unsigned char crc_8bit[2] ;
};

extern union crc_buf_t crc;
extern void calccrc(unsigned char crcbuf);

#endif // _HACDEVICEMANAGER_H_
