#ifndef _HACHELP_H_
#define _HACHELP_H_

#include <QString>
#include <QStringList>
#include <QSize>

/*
 * help definition
 */
#define SizeOfArray(array) (sizeof(array)/sizeof(*(array)))


/*
 * hac help class
 */
class HacHelp {
public:
	static QString Size2String(const QSize &size);
	static QString Int2InverseString(int i);
	static QString HexString(quint8 num, bool withDec = false);
	static QString HexString(quint16 num, bool withDec = false);
	static QString HexString(quint32 num, bool withDec = false);
	static bool IntCmp(quint32 n1, quint32 n2, const QString &cond);

	static void MSleep(int ms);

	static void FixQSettings(const QString &oldName, const QString &newName);
	static void FixQSettings_RemoveOrderKey(QString &key);

	static QString ReadStyleSheetFromFile(const QString &filename);

	static qreal Fahrenheit2Celsius(qreal temp);
	static qreal Celsius2Fahrenheit(qreal temp);

	static qreal AngleToRadian(qreal angle);
	static qreal RadianToAngle(qreal radian);

private:

};

#endif // _HACHELP_H_
