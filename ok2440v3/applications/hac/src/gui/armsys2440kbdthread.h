#include <QDebug>
#include <QWidget>
#include <QThread>
#include <QMutex>
#include <QReadWriteLock>
#include <QWSServer>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>


class ArmSys2440KbdThread : public QThread {
	Q_OBJECT

public:
	ArmSys2440KbdThread(QObject *parent = NULL)
	: QThread(parent) {

		qDebug() << "ArmSys2440KbdThread::ArmSys2440KbdThread";

		int buttons_fd;
		buttons_fd = open("/dev/buttons", 0);
		if (buttons_fd < 0) {
			perror("open device buttons");
		}
	}

	~ArmSys2440KbdThread()
	{
		qDebug() << "ArmSys2440KbdThread::~ArmSys2440KbdThread";

		close(buttons_fd);
	}

	void stop()
	{
        d_rwLock.lockForWrite();
        d_beStopped = true;
        d_rwLock.unlock();
	}


protected:
	void run()
	{
		qDebug() << "ArmSys2440KbdThread::run";

		if (buttons_fd < 0)
			return;

		d_beStopped = false;

		forever {
			d_rwLock.lockForRead();
			if (d_beStopped) {
				d_rwLock.unlock();
				break;
			}
			d_rwLock.unlock();

			fd_set rds;
			int ret;
			int key_value;
			int key_code;

			FD_ZERO(&rds);
			FD_SET(buttons_fd, &rds);

			qDebug() << "ArmSys2440KbdThread::run select1";

			ret = select(buttons_fd + 1, &rds, NULL, NULL, NULL);

			qDebug() << "ArmSys2440KbdThread::run select2";

			if (ret < 0) {
				perror("select");
				break;
			}

			if (ret == 0) {
				printf("Timeout.\n");
			} else if (FD_ISSET(buttons_fd, &rds)) {
				int ret = read(buttons_fd, &key_value, sizeof key_value);
				if (ret != sizeof key_value) {
					if (errno != EAGAIN)
						perror("read buttons\n");
					continue;
				} else {
					printf("buttons_value: %d\n", key_value);

					// process key event
					switch (key_value) {
					case 1:
					case 2:
					case 3:
						break;
					case 4:
                        //QWSServer::sendKeyEvent(0xFFFF, Qt::Key_Back,0, true, false);

						{
							qDebug() << "back button pressed ...";
							QWidget *widget = QApplication::topLevelAt(160, 120);
							if (widget->objectName() != "HacTaskPanel"
								&& widget->objectName() != "MainHomePage") {
								widget->close();
							}
						}

						break;
					case 129:
					case 130:
					case 131:
						break;
					case 132:
                        //QWSServer::sendKeyEvent(0xFFFF, Qt::Key_Back,0, false, false);
						break;
					default:
						break;
					}
				}
			}
		}
	}

	private:
		QReadWriteLock d_rwLock;
		bool d_beStopped;
		int buttons_fd;
};

