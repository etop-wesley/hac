//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QApplication>
#include "upgradermain.h"


int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	qDebug() << "main" << app.arguments();
	app.setQuitOnLastWindowClosed(true);
	QStringList args(app.arguments());
	QString image, bootLoader, bootParam, bootImage, kernel, rootFs;
	for (int i = 1; i < args.size(); ++i)
	{
		if(args.at(i).startsWith("--")) {
			if(args.at(i) == "--image" && i + 1 < args.size())
				image = args.at(++i);
			else if(args.at(i) == "--bootloader" && i+1 < args.size())
				bootLoader = args.at(++i);
			else if(args.at(i) == "--bootparam" && i+1 < args.size())
				bootParam = args.at(++i);
			else if(args.at(i) == "--bootimage" && i+1 < args.size())
				bootImage = args.at(++i);
			else if(args.at(i) == "--kernel" && i+1 < args.size())
				kernel = args.at(++i);
			else if(args.at(i) == "--rootfs" && i+1 < args.size())
				rootFs = args.at(++i);
			else
				qDebug() << "unknown argument" << args.at(i);
		}
	}


	UpgraderMain um;
	um.setFilePath(image);
	um.setBootLoaderFilePath(bootLoader);
	um.setBootParamFilePath(bootParam);
	um.setBootImageFilePath(bootImage);
	um.setKernelFilePath(kernel);
	um.setRootFsFilePath(rootFs);

	um.showMaximized();

	return app.exec();
}
