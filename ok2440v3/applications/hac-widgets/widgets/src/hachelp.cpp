//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>

#include "hachelp.h"
#if defined(Q_OS_WIN32)
	#include <windows.h>
#elif defined(Q_OS_LINUX) | defined(Q_OS_UNIX)
	#include <unistd.h> 
#endif
#include <QDebug>
#include <QFile>
#include <QByteArray>

#ifndef PI
#define PI 3.14159265358979323846
#endif


QString HacHelp::Size2String(const QSize &size)
{
	return QString::number(size.width()) + " x " + QString::number(size.height());
}

QString HacHelp::Int2InverseString(int i)
{
	return i == 0 ? QString("0") : QString("1 / %1").arg(i);
}

QString HacHelp::HexString(quint8 num, bool withDec)
{
	if (withDec)
		return QString("%1(%2)").arg(num, 2, 16, QChar('0')).arg(num).toUpper().prepend("0x");
	else
		return QString("%1").arg(num, 2, 16, QChar('0')).toUpper().prepend("0x");
}

QString HacHelp::HexString(quint16 num, bool withDec)
{
	if (withDec)
		return QString("%1(%2)").arg(num, 4, 16, QChar('0')).arg(num).toUpper().prepend("0x");
	else
		return QString("%1").arg(num, 4, 16, QChar('0')).toUpper().prepend("0x");
}

QString HacHelp::HexString(quint32 num, bool withDec)
{
	if (withDec)
		return QString("%1(%2)").arg(num, 8, 16, QChar('0')).arg(num).toUpper().prepend("0x");
	else
		return QString("%1").arg(num, 8, 16, QChar('0')).toUpper().prepend("0x");
}

bool HacHelp::IntCmp(quint32 n1, quint32 n2, const QString &cond)
{
	if ((cond == "==") || (cond == "="))
		return n1 == n2;
	else if (cond == "!=")
		return n1 != n2;
	else if (cond == ">")
		return n1 > n2;
	else if (cond == ">=")
		return n1 >= n2;
	else if (cond == "<")
		return n1 < n2;
	else if (cond == "<=")
		return n1 <= n2;
	return false;
}

void HacHelp::MSleep(int ms)
{
	qDebug() << "HacHelp::MSleep" << ms;
#if defined(Q_OS_WIN32)
	Sleep(ms);
#elif defined(Q_OS_LINUX) | defined(Q_OS_UNIX)
	usleep(ms*1000);
#endif
}

/*
 * fix the QSettings auto sortting problem
 */
void HacHelp::FixQSettings(const QString &oldName, const QString &newName)
{
	QFile oldFile(oldName);
	if (!oldFile.open(QIODevice::ReadOnly))
		return;

	QFile newFile(newName);
	if (!newFile.open(QIODevice::WriteOnly))
		return;

	uint i = 0;
	uint uint_max = (uint)(-1);
	int uint_max_bits = 1;
	while (uint_max > 0) {
		uint_max_bits ++;
		uint_max /= 10;
	}

	while (!oldFile.atEnd()) {
		QByteArray line = oldFile.readLine();
		if (!line.isEmpty()) {
			if (line.startsWith(";") || line.startsWith("//")) { // is a comment line
				// we don't want the comment
				continue;
			} else if (((line.size() == 2) && (line[0] == '\r') && (line[1] == '\n')) // win32 format: '\r''\n'
					   || ((line.size() == 1) && (line[0] == '\n'))	// unix format: '\n'
					   || ((line.size() == 1) && (line[0] == '\r'))) { // mac format: '\r'
				// inside a group, and it is a "new line"
				// ignore it
				continue;
			} else { // the line we want
				bool isGroup = false;
				// remove line comment
				if (line.startsWith("[") && line.contains("]")) { // is a group start line
					isGroup = true;
				}

				int comment = -1, comment1 = -1, comment2 = -1;
				if (isGroup) {
					int ge = line.indexOf("]");
					comment1 = line.indexOf("//", ge);
					comment2 = line.indexOf(";", ge);
				} else {
					comment1 = line.indexOf("//");
					comment2 = line.indexOf(";");
				}

				if ((comment1 < 0) && (comment2 < 0)) // not comment
					comment = -1;
				else if ((comment1 > 0) || (comment2 > 0))
					comment = qMax(comment1, comment2);
				else if ((comment1 > 0) && (comment2 > 0))
					comment = qMin(comment1, comment2);

				if (comment >= 0) {
					line.remove(comment, line.size()); // specific n to size for removing all elements from p	
				}

				if (isGroup) {
					i = 0;
				} else {
					i ++;
					line.prepend(QString(QString::number(i) + ": ").toAscii());
					int i_tmp = i;
					int i_bits = 1;
					while (i_tmp > 0) {
						i_bits ++;
						i_tmp /= 10;
					}
					for (int i = 0; i <= uint_max_bits - i_bits; i++)
						line.prepend('0');
				}
			}

			if (line.endsWith("\r\n"))
				line.remove(line.size() - 2, 2);
			else if (line.endsWith("\n"))
				line.remove(line.size() - 1, 1);
			else if (line.endsWith("\r"))
				line.remove(line.size() - 1, 1);
#if defined(Q_OS_WIN)
			line.append("\r\n");
#elif defined(Q_OS_UNIX) || defined(Q_OS_LINUX)
			line.append("\n");
#elif defined(Q_OS_MAC)
			line.append("\r");
#else
			line.append("\r\n");
#endif
			newFile.write(line);
		}
	}
}

void HacHelp::FixQSettings_RemoveOrderKey(QString &key)
{
	int index = key.indexOf(": ");
	bool ok = false;
	if (index == -1 && !key.left(index).toUInt(&ok))
		return;

	key.remove(0, index + 2);
}


QString HacHelp::ReadStyleSheetFromFile(const QString &filename)
{
     QFile file(filename);
     file.open(QFile::ReadOnly);
	 return QLatin1String(file.readAll());
}

qreal HacHelp::Fahrenheit2Celsius(qreal temp)
{
	return (qreal)(temp * 9) / 5 + 32;
}

qreal HacHelp::Celsius2Fahrenheit(qreal temp)
{
	return (qreal)((temp - 32) * 5) / 9;
}

qreal HacHelp::AngleToRadian(qreal angle)
{
	return angle * PI / 180.0;
}

qreal HacHelp::RadianToAngle(qreal radian)
{
	return radian * 180.0 / PI;
}
