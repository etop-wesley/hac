//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QStringList>
#include <QSysInfo>
#include <QLibraryInfo>
#include "hac-config.h"
#include "hacapplication.h"

#include <QFile>
#include <QString>
#include <QByteArray>
#include <QStringList>

static int buttons_fd;


HacApplication::HacApplication(int &argc, char **argv)
: QApplication(argc, argv)
{
	qDebug() << "HacApplication::HacApplication" << arguments();

	QCoreApplication::setOrganizationName(HAC_ORG_NAME);
	QCoreApplication::setOrganizationDomain(HAC_ORG_DOMAIN);
	QCoreApplication::setApplicationName(HAC_APP_NAME);
	QCoreApplication::setApplicationVersion(HAC_VER);

	setQuitOnLastWindowClosed(true);


	//kbdThread = new ArmSys2440KbdThread(this);
	//kbdThread->start();
	kbdTimer = new QTimer(this);
	kbdTimer->setInterval(100);
	kbdTimer->start();
	connect(kbdTimer, SIGNAL(timeout()), this, SLOT(on_read_buttons()));

	switchTimer = new QTimer(this);
	switchTimer->setSingleShot(true);
	switchTimer->setInterval(5000);
	connect(switchTimer, SIGNAL(timeout()), this, SLOT(on_switch_app()));
	d_switchApp = 0;


	buttons_fd = open("/dev/buttons", 0);
}

HacApplication::~HacApplication()
{
	qDebug() << "HacApplication::~HacApplication";
	//kbdThread->stop();
	//kbdThread->wait();
	close(buttons_fd);
}

HacApplication * HacApplication::instance()
{
	static bool check = false;
	static HacApplication *instance = 0;

	if (!check) {
		if (qApp) {
			instance = qobject_cast<HacApplication *>(qApp);
			check = (bool)instance;
		}
	}

	return instance;
}

void HacApplication::on_read_buttons()
{
   // qDebug() << "HacApplication::on_read_buttons";
	fd_set rds;
	int ret;
	int key_value;
	int key_code;

	if (buttons_fd < 0) {
		return;
	}

	FD_ZERO(&rds);
	FD_SET(buttons_fd, &rds);

	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 1000;

	ret = select(buttons_fd + 1, &rds, NULL, NULL, &tv);

	if (ret < 0) {
		return;

	}

	if (ret == 0) {
		//printf("Timeout.\n");
		return;
	} else if (FD_ISSET(buttons_fd, &rds)) {
		int ret = read(buttons_fd, &key_value, sizeof key_value);
		if (ret != sizeof key_value) {
			if (errno != EAGAIN)
				perror("read buttons\n");
			return;
		} else {
			//printf("buttons_value: %d\n", key_value);

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
					if (widget->objectName() != "HacMainWindow") {
						widget->close();
					}

					switchTimer->start();

				}

				break;
			case 129:
			case 130:
			case 131:
				break;
			case 132:
				switchTimer->stop();

				//QWSServer::sendKeyEvent(0xFFFF, Qt::Key_Back,0, false, false);
				break;
			default:
				break;
			}
		}
	}

}



static void startHac()
{
	system("/usr/bin/hac -qws  &");
}

static void startHacTianyu()
{
	system("/usr/bin/hac-tianyu -qws  &");
}

int killall(const QString &name)
{
	qDebug() << "killall name ..." << name;
	QString command = "ps -ef";
	command += " > /tmp/ps-output";
	qDebug() << "ps ...";
	if (system(command.toAscii().constData()) != 0)
		return -1;

	qDebug() << "open ps file ...";
    QFile psFile("/tmp/ps-output");
     if (!psFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
			qDebug() << psFile.errorString();
			 return -1;
	 }

	 QByteArray line;
	 QString temp;
	 while (!psFile.atEnd()) {
         line = psFile.readLine();
		 if (line.contains(name.toAscii().constData())) {
			 temp = line;
			 temp = temp.split(" ", QString::SkipEmptyParts).at(0);

			 command = "kill -9 ";
			 command += temp;
			 qDebug() << command;

			 if (name == "/usr/bin/hac") {
				 qAddPostRoutine(startHacTianyu);
			 } else if (name == "/usr/bin/hac-tianyu") {
				 qAddPostRoutine(startHac);
			 }
			 if (system(command.toAscii().constData()) != 0)
				 return -1;
			 else
				 return 1;
		 }
     }

	 return 0;
}


void HacApplication::on_switch_app()
{
	qDebug() << "HacApplication::on_switch_app";

	d_switchApp = 2;

	QApplication::quit();

}


