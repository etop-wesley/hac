#ifndef _UPGRADERMAIN_H_
#define _UPGRADERMAIN_H_

#include <QWidget>
#include <QProcess>
#include <QTimer>

namespace Ui {
    class UpgraderMain;
}

class UpgraderMain : public QWidget {
    Q_OBJECT
public:
    UpgraderMain(QWidget *parent = NULL);
    ~UpgraderMain();

	void setFilePath(const QString &);
	void setBootLoaderFilePath(const QString &);
	void setBootParamFilePath(const QString &);
	void setBootImageFilePath(const QString &);
	void setKernelFilePath(const QString &);
	void setRootFsFilePath(const QString &);

	bool upgrade();

public Q_SLOTS:

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void  on_upgradeProcess_error(QProcess::ProcessError);
	void  on_upgradeProcess_finished (int, QProcess::ExitStatus);
	void  on_upgradeProcess_readyReadStandardError();
	void  on_upgradeProcess_readyReadStandardOutput();
	void  on_upgradeProcess_started();
	void  on_upgradeProcess_stateChanged(QProcess::ProcessState);

	void OnOkButtonClicked();
	void OnCancelButtonClicked();

	void OnTimeout();

private:
	void read(const QByteArray &);
	bool _erase_and_write(const QString &mtd, const QString &file);

private:
    Ui::UpgraderMain *ui;
	// auto start timer
	QTimer *d_timer;
	// upgrade process
	QProcess *d_upProc;
	// upgrade image path
	QString d_filePath;
	// boot loader path
	QString d_bootLoaderPath;
	// boot param path
	QString d_bootParamPath;
	// bootloader image path
	QString d_bootImagePath;
	// kernel path
	QString d_kernelPath;
	// rootfs path
	QString d_rootFsPath;
};

#endif // _UPGRADERMAIN_H_

