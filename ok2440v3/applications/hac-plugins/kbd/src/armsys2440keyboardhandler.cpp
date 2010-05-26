
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "linux/i2c-algo-gm.h"

#include <qglobal.h>
#include <qtimer.h>
#include "armsys2440keyboardhandler.h"

/*
 * IR Data Format:
 * Customer Code Low + Customer Code High + Key Code + Check Sum
 * Customer Code Low = 0x04
 * Customer Code High = 0xF3
 * Key Code = see below
 * Check Sum = Customer Code Low + Customer Code High + Key Code
 */

/* 
 * Key Value Definition 
 */
#define KEY_NONE		0x00
#define KEY_POWER		0x01
#define KEY_1			0x02
#define KEY_2			0x03
#define KEY_3			0x04
#define KEY_4			0x05
#define KEY_5			0x06
#define KEY_6			0x07
#define KEY_7			0x08
#define KEY_8			0x09
#define KEY_9			0x0A
#define KEY_OK			0x0B
#define KEY_0			0x0C
#define KEY_REPEAT		0x0D
#define KEY_UNMARK		0x0E
#define KEY_FAVORITE	0x0F
#define KEY_UP			0x10
#define KEY_LEFT		0x11
#define KEY_PLAY		0x12
#define KEY_RIGHT		0x13
#define KEY_DOWN		0x14
#define KEY_STOP		0x15
#define KEY_PRESET		0x16
#define KEY_HOME		0x17
#define KEY_CANCEL	  	0x18
#define KEY_SYSTEM		0x19
#define KEY_MARK		0x1A
#define KEY_FORWARD		0x1B
#define KEY_PLUS		0x1C
#define KEY_MUTE		0x1D
#define KEY_MINUS		0x1E
#define KEY_BACKWARD	0x1F
#define KEY_INFO		0x4C
#define KEY_F1			0x41
#define KEY_F2			0x42
#define KEY_F3			0x43
#define KEY_F4			0x44

#define KEY_NUMS		37

/*
 * Qt Key Code Mapping
 */
static const QWSKeyMap IrKeyMap[] = {
	{ Qt::Key_unknown, 0xffff, 0xffff, 0xffff }, // KEY_NONE
	{ Qt::Key_Standby, 0xffff, 0xffff, 0xffff }, // KEY_POWER
	{ Qt::Key_1, '1', 0xffff, 0xffff }, // KEY_1
	{ Qt::Key_2, '2', 0xffff, 0xffff }, // KEY_2
	{ Qt::Key_3, '3', 0xffff, 0xffff }, // KEY_3
	{ Qt::Key_4, '4', 0xffff, 0xffff }, // KEY_4
	{ Qt::Key_5, '5', 0xffff, 0xffff }, // KEY_5
	{ Qt::Key_6, '6', 0xffff, 0xffff }, // KEY_6
	{ Qt::Key_7, '7', 0xffff, 0xffff }, // KEY_7
	{ Qt::Key_8, '8', 0xffff, 0xffff }, // KEY_8
	{ Qt::Key_9, '9', 0xffff, 0xffff }, // KEY_9
	{ Qt::Key_Super_L, 0xffff, 0xffff, 0xffff }, // KEY_OK
	{ Qt::Key_0, '0', 0xffff, 0xffff }, // KEY_0
	{ Qt::Key_F11, 0xffff, 0xffff, 0xffff }, // KEY_REPEAT
	{ Qt::Key_Delete, 0xffff, 0xffff, 0xffff }, // KEY_UNMARK
	{ Qt::Key_Favorites, 0xffff, 0xffff, 0xffff }, // KEY_FAVORITE
	{ Qt::Key_Up, 0xffff, 0xffff, 0xffff }, // KEY_UP
	{ Qt::Key_Left, 0xffff, 0xffff, 0xffff }, // KEY_LEFT
	{ Qt::Key_Enter, 0xffff, 0xffff, 0xffff }, // KEY_PLAY
	{ Qt::Key_Right, 0xffff, 0xffff, 0xffff }, // KEY_RIGHT
	{ Qt::Key_Down, 0xffff, 0xffff, 0xffff }, // KEY_DOWN
	{ Qt::Key_Stop, 0xffff, 0xffff, 0xffff }, // KEY_STOP
	{ Qt::Key_F12, 0xffff, 0xffff, 0xffff }, // KEY_PRESET
	{ Qt::Key_HomePage, 0xffff, 0xffff, 0xffff }, // KEY_HOME
	{ Qt::Key_Super_R, 0xffff, 0xffff, 0xffff }, // KEY_CANCEL
	{ Qt::Key_SysReq, 0xffff, 0xffff, 0xffff }, // KEY_SYSTEM
	{ Qt::Key_Insert, 0xffff, 0xffff, 0xffff }, // KEY_MARK
	{ Qt::Key_Forward, 0xffff, 0xffff, 0xffff }, // KEY_FORWARD
	{ Qt::Key_VolumeUp, 0xffff, 0xffff, 0xffff }, // KEY_PLUS
	{ Qt::Key_VolumeMute, 0xffff, 0xffff, 0xffff }, // KEY_MUTE
	{ Qt::Key_VolumeDown, 0xffff, 0xffff, 0xffff }, // KEY_MINUS
	{ Qt::Key_Back, 0xffff, 0xffff, 0xffff }, // KEY_BACKWARD
	{ Qt::Key_Help, 0xffff, 0xffff, 0xffff }, // KEY_INFO
	{ Qt::Key_F1, 0xffff, 0xffff, 0xffff }, // KEY_F1
	{ Qt::Key_F2, 0xffff, 0xffff, 0xffff }, // KEY_F2
	{ Qt::Key_F3, 0xffff, 0xffff, 0xffff }, // KEY_F3
	{ Qt::Key_F4, 0xffff, 0xffff, 0xffff }, // KEY_F4
	{ 0, 0xffff, 0xffff, 0xffff } // unknow
};

static const int keyMapSize = sizeof(IrKeyMap)/sizeof(QWSKeyMap)-1;

#define I2C_DEVICE		("/dev/i2c-0")
#define I2C_RD			(0x01)
#define I2C_WR			(0x00)
#define IR_ADDR			(0xA0)
#define IR_OFFSET		(0x00)
#define IR_DATA_LEN		(4)
#define IR_KEY_INDEX	(2)

#define KBD_POLL_INTERVAL (80) //ms

class MIrKeyboardHandlerPrivate : public QObject {
	Q_OBJECT

	public:
	MIrKeyboardHandlerPrivate(MIrKeyboardHandler *h, const QString &device);
	~MIrKeyboardHandlerPrivate();

	void suspend();
	void resume();

private slots:
	void readKeyboardData();

private:
	bool open();
	void close();

private:
	int m_kbdFd;
	QTimer *m_pollTimer;
	MIrKeyboardHandler *m_handler;
};

/*
 * Constructs MIrKeyboardHandlerPrivate handler.
 */
MIrKeyboardHandlerPrivate::MIrKeyboardHandlerPrivate(MIrKeyboardHandler *h, const QString &device)
: QObject(), m_handler(h)
{
	qDebug("MIrKeyboardHandlerPrivate::MIrKeyboardHandlerPrivate %s\n", device.local8Bit().data());
	m_kbdFd = ::open(device.local8Bit().data(), O_RDONLY|O_NONBLOCK);
	m_pollTimer = NULL;
	if (m_kbdFd >= 0) {
		qDebug("Opened %s as keyboard input\n", device.local8Bit().data());
		/* the i2c driver is break with select call, 
		   so we can not use QSocketNotifier to watch the device.
		   use a polling QTimer instead. 
		 */
		m_pollTimer = new QTimer(this);
		connect(m_pollTimer, SIGNAL(timeout()), this, SLOT(readKeyboardData()));
		m_pollTimer->start(KBD_POLL_INTERVAL);
	} else {
		qWarning("Can not open %s, %s\n", device.local8Bit().data(), strerror(errno));
	}
}

/*
 * Destroys MIrKeyboardHandlerPrivate handler
 */
MIrKeyboardHandlerPrivate::~MIrKeyboardHandlerPrivate()
{
	qDebug("MIrKeyboardHandlerPrivate::~MIrKeyboardHandlerPrivate\n");
	if (m_pollTimer != NULL) {
		m_pollTimer->stop();
		delete m_pollTimer;
		m_pollTimer = NULL;
	}

	if (m_kbdFd >= 0) {
		::close(m_kbdFd);
		m_kbdFd = -1;
	}
}

/*
 * read keyboard data slot, and process the key event to QWSServer
 */
void MIrKeyboardHandlerPrivate::readKeyboardData()
{
	struct i2c_gm_msg i2c_ap ;
	char ir_data[IR_DATA_LEN] = {0};

	i2c_ap.clockdiv = 0;
	i2c_ap.addr = IR_ADDR | I2C_RD;
	i2c_ap.waddr = IR_OFFSET;
	i2c_ap.len = IR_DATA_LEN;
	i2c_ap.buf = ir_data;
	i2c_ap.multiread_once = 1;

	// read IR data with I2C interface
	if (::ioctl(m_kbdFd, I2C_RDWR, &i2c_ap) != IR_DATA_LEN) {
		qWarning("MIrKeyboardHandler::readKbdData ioctl: %s\n", strerror(errno));
		::sleep(1);
		return;
	} else if (ir_data[0] == 0) { // no ir data read
		return;
	}

	// send out a press+release pair immediately
	int key = ir_data[IR_KEY_INDEX];
	if ((key >= 0) && (key <= keyMapSize - 1)) {
        int keyCode = IrKeyMap[key].key_code;
		int unicode = IrKeyMap[key].unicode;
		qDebug("MIrKeyboardHandler::readKbdData key=0x%X (%d), keyCode=0x%X (%d), unicode=0x%X (%d)\n", key, key, keyCode, keyCode, unicode, unicode);
		m_handler->processKeyEvent(unicode, keyCode, 0, true, false);
		m_handler->processKeyEvent(unicode, keyCode, 0, false, false);
	}
}

/*
 * Constructs MIrKeyboardHandler handler.
 */
MIrKeyboardHandler::MIrKeyboardHandler(const QString &driver, const QString &device)
: QWSKeyboardHandler()
{
	Q_UNUSED(driver);
	d = new MIrKeyboardHandlerPrivate(this, device);
}

/*
 * Destroys MIrKeyboardHandler handler
 */
MIrKeyboardHandler::~MIrKeyboardHandler()
{
	delete d;
}

/*
 * This will cause the moc-generated code to be compiled 
 * and linked together with the normal class definition
 */
#include "mirkeyboardhandler.moc"
