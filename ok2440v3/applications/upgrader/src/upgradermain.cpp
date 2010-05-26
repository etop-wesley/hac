//define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QFile>
#include <QTimer>
#include "upgradermain.h"
#include "ui_upgradermain.h"

#define MTD_DEV_BOOTLOADER "/dev/mtd/0"
#define MTD_DEV_BOOTPARAM "/dev/mtd/1"
#define MTD_DEV_BOOTIMAGE "/dev/mtd/2"
#define MTD_DEV_KERNEL "/dev/mtd/2"
#define MTD_DEV_ROOTFS "/dev/mtd/3"

#define MTD_UTIL_ERASEALL_BIN "/usr/sbin/flash_eraseall"
#define MTD_UTIL_ERASEALL_OPTIONS ""
#define MTD_UTIL_NANDWRITE_BIN "/usr/sbin/nandwrite"
#define MTD_UTIL_NANDWRITE_OPTIONS "-p"

UpgraderMain::UpgraderMain(QWidget *parent)
:   QWidget(parent),
	ui(new Ui::UpgraderMain)
{
	qDebug() << "UpgraderMain::UpgraderMain";
	ui->setupUi(this);
	ui->progressBar->setRange(0, 100);
	d_upProc = new QProcess(this);
	d_timer = new QTimer(this);
	d_timer->setSingleShot(true);

	connect(d_upProc, SIGNAL(error (QProcess::ProcessError)), this, SLOT(on_upgradeProcess_error(QProcess::ProcessError)));
	connect(d_upProc, SIGNAL(finished (int, QProcess::ExitStatus)), this, SLOT(on_upgradeProcess_finished (int, QProcess::ExitStatus)));
	connect(d_upProc, SIGNAL(readyReadStandardError()), this, SLOT(on_upgradeProcess_readyReadStandardError()));
	connect(d_upProc, SIGNAL(readyReadStandardOutput()), this, SLOT(on_upgradeProcess_readyReadStandardOutput()));
	connect(d_upProc, SIGNAL(started()), this, SLOT(on_upgradeProcess_started()));
	connect(d_upProc, SIGNAL(stateChanged (QProcess::ProcessState)), this, SLOT(on_upgradeProcess_stateChanged(QProcess::ProcessState)));
	connect(d_timer, SIGNAL(timeout ()), this, SLOT(OnTimeout()));
	connect(ui->okButton, SIGNAL(clicked ()), this, SLOT(OnOkButtonClicked()));
	connect(ui->cancelButton, SIGNAL(clicked ()), this, SLOT(OnCancelButtonClicked()));

    ui->infoLabel->setText(tr("You are going to update your system now. Continue?\n"
							  "\n"
							  "The update will be automatically started after 10 seconds, if you are unable to push the button!"));
	d_timer->start(10*1000);
}

UpgraderMain::~UpgraderMain()
{
	qDebug() << "UpgraderMain::~UpgraderMain";
	delete d_timer;
	delete d_upProc;
	delete ui;
}

void UpgraderMain::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}

void UpgraderMain::setFilePath(const QString &path)
{
	d_filePath =  path;
}

void UpgraderMain::setBootLoaderFilePath(const QString &path)
{
	d_bootLoaderPath =  path;
}

void UpgraderMain::setBootParamFilePath(const QString &path)
{
	d_bootParamPath =  path;
}

void UpgraderMain::setBootImageFilePath(const QString &path)
{
	d_bootImagePath =  path;
}

void UpgraderMain::setKernelFilePath(const QString &path)
{
	d_kernelPath =  path;
}

void UpgraderMain::setRootFsFilePath(const QString &path)
{
	d_rootFsPath =  path;
}


void UpgraderMain::OnTimeout()
{
	OnOkButtonClicked();
}

void UpgraderMain::OnOkButtonClicked()
{
	ui->okButton->hide();
	ui->cancelButton->hide();
	d_timer->stop();
	upgrade();

	qDebug() << "OnOkButtonClicked upgrade";

	ui->infoLabel->setText(tr("Update completed!\n"
							  "\n"
							  "Please unplug the storage device, and reboot your system now."));
	//close();
}

void UpgraderMain::OnCancelButtonClicked()
{
	ui->okButton->hide();
	ui->cancelButton->hide();
	d_timer->stop();
	ui->infoLabel->setText(tr("Update cancelled!\n"
							  "\n"
							  "Please unplug the storage device, and reboot your system now."));
	//close();
}

bool UpgraderMain::upgrade()
{
	//_erase_and_write(MTD_DEV_BOOTLOADER, d_bootLoaderPath);
	//_erase_and_write(MTD_DEV_BOOTPARAM, d_bootParamPath);
	//_erase_and_write(MTD_DEV_BOOTIMAGE, d_bootImagePath);
	_erase_and_write(MTD_DEV_KERNEL, d_kernelPath);
	_erase_and_write(MTD_DEV_ROOTFS, d_rootFsPath);
}

bool UpgraderMain::_erase_and_write(const QString &mtd, const QString &file)
{
	qDebug() << "_erase_and_write" << mtd << file;

	if (!QFile::exists(mtd) || !QFile::exists(file))
		return false;

	if (d_upProc->state() != QProcess::NotRunning) {
		qDebug() << "UpgraderMain::upgrade QProcess::state";
		return false;
	}

	ui->progressBar->reset();

	QString arguments;
	arguments = MTD_UTIL_ERASEALL_OPTIONS;
	arguments += " ";
	arguments += mtd;
	qDebug() << arguments.split(' ', QString::SkipEmptyParts);

	d_upProc->start(MTD_UTIL_ERASEALL_BIN, arguments.split(' ', QString::SkipEmptyParts));
	qDebug() << "UpgraderMain::upgrade waitForStarted";
	if (!d_upProc->waitForStarted(-1)) {
		qDebug() << "UpgraderMain::upgrade QProcess::waitForStarted";
		return false;
	}
	qDebug() << "UpgraderMain::upgrade waitForStarted Started";

	qDebug() << "UpgraderMain::waitForFinished";
	if (!d_upProc->waitForFinished(-1)) {
		qDebug() << "UpgraderMain::upgrade QProcess::waitForFinished";
		return false;
	}
	qDebug() << "UpgraderMain::waitForFinished Finished";

	qDebug() << "UpgraderMain::upgrade QProcess::state" << d_upProc->state();

	ui->progressBar->reset();

	arguments = MTD_UTIL_NANDWRITE_OPTIONS;
	arguments += " ";
	arguments += mtd;
	arguments += " ";
	arguments += file;

	qDebug() << arguments.split(' ', QString::SkipEmptyParts);

	d_upProc->start(MTD_UTIL_NANDWRITE_BIN, arguments.split(' ', QString::SkipEmptyParts));
	qDebug() << "UpgraderMain::waitForStarted";
	if (!d_upProc->waitForStarted(-1)) {
		qDebug() << "UpgraderMain::upgrade QProcess::waitForStarted";
		return false;
	}
	qDebug() << "UpgraderMain::upgrade waitForStarted Started";

	qDebug() << "UpgraderMain::waitForFinished";
	if (!d_upProc->waitForFinished(-1)) {
		qDebug() << "UpgraderMain::upgrade QProcess::waitForFinished";
		return false;
	}
	qDebug() << "UpgraderMain::waitForFinished Finished";

	qDebug() << "UpgraderMain::upgrade QProcess::state" << d_upProc->state();
	return true;
}

void  UpgraderMain::on_upgradeProcess_error (QProcess::ProcessError error)
{
	qDebug() << "UpgraderMain::on_upgradeProcess_error" << error;
}

void  UpgraderMain::on_upgradeProcess_finished (int exitCode, QProcess::ExitStatus exitStatus)
{
	qDebug() << "UpgraderMain::on_upgradeProcess_finished" << exitCode << exitStatus;
}

void  UpgraderMain::on_upgradeProcess_readyReadStandardError()
{
	//qDebug() << "UpgraderMain::on_upgradeProcess_readyReadStandardError";
	read(d_upProc->readAllStandardError());
}

void  UpgraderMain::on_upgradeProcess_readyReadStandardOutput()
{
	//qDebug() << "UpgraderMain::on_upgradeProcess_readyReadStandardOutput";
	read(d_upProc->readAllStandardOutput ());
}

void  UpgraderMain::on_upgradeProcess_started()
{
	qDebug() << "UpgraderMain::on_upgradeProcess_started";
}

void  UpgraderMain::on_upgradeProcess_stateChanged(QProcess::ProcessState newState)
{
	qDebug() << "UpgraderMain::on_upgradeProcess_stateChanged" << newState;

}

void UpgraderMain::read(const QByteArray &data)
{
	qDebug() << "UpgraderMain::read" << QString(data);
	if (ui->progressBar->value() == 100)
		ui->progressBar->setValue(0);
	else
		ui->progressBar->setValue(ui->progressBar->value() + 1);
	QApplication::flush();
	QApplication::processEvents();
}

