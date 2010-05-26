//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "haccore.h"

HacCore::HacCore(QObject *parent)
: QObject(parent)
{
	qDebug() << "HacCore::HacCore";
}

HacCore::~HacCore()
{
	qDebug() << "HacCore::~HacCore";
}
