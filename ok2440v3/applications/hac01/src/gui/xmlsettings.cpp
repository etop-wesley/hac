//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>

#include "xmlsettings.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QStringList>

static bool readXmlFile(QIODevice &device, QSettings::SettingsMap &map);
static bool writeXmlFile(QIODevice &device, const QSettings::SettingsMap &map);

namespace XmlSettings {
/* 
 * registered XML format read/write functions
 * On success, returns a special Format value that can then be passed to the QSettings constuctor.
 * On failure, returns InvalidFormat.
 */
QSettings::Format XmlFormat = QSettings::registerFormat("xml", readXmlFile, writeXmlFile);
}

/* XML root note name */
#define XML_ROOT_NAME "root"

/* 
 * QSettings ReadFunc
 * ReadFunc is used in registerFormat() as a pointer to a function
 * that reads a set of key/value pairs.
 * ReadFunc should read all the options in one pass,
 * and return all the settings in the SettingsMap container,
 * which is initially empty.
 */
static bool readXmlFile(QIODevice& device, QSettings::SettingsMap& map)
{
	QXmlStreamReader xmlReader(&device);
	QStringList currentElementName;

	while (!xmlReader.atEnd()) {
		xmlReader.readNext();
		if (xmlReader.name() == XML_ROOT_NAME) {
			xmlReader.readNext();
			continue;
		}

		while (xmlReader.isStartElement()) {
			const QString element = xmlReader.name().toString();

			int iSeparator = element.indexOf('.');

			if (iSeparator==-1)
				currentElementName.push_back(element);
			else {
				currentElementName.push_back(element.right(element.length() - iSeparator - 1));
				currentElementName.push_back(element.left(iSeparator));
			}
			xmlReader.readNext();
		}

		if (xmlReader.isEndElement()) {
			const QString element = xmlReader.name().toString();
			currentElementName.pop_back();
			if (element.indexOf('.') != -1)
				currentElementName.pop_back();
			continue;
		}

		if (xmlReader.isCharacters() && !xmlReader.isWhitespace()) {
			QString key = currentElementName.join("/");
			QString value = xmlReader.text().toString();
			map[key] = value;
		}
	}

	if (xmlReader.hasError())
		return false;
	return true;
}

/*
 * QSettings WriteFunc
 * WriteFunc is used in registerFormat() as a pointer to a function
 * that writes a set of key/value pairs.
 * WriteFunc is only called once, so you need to output the settings in one go.
 */
static bool writeXmlFile(QIODevice &device, const QSettings::SettingsMap &map)
{
	QXmlStreamWriter xmlWriter(&device);
	xmlWriter.setAutoFormatting(true);

	xmlWriter.writeStartDocument();
	xmlWriter.writeStartElement(XML_ROOT_NAME);

	QStringList treeGroups;

	for (QSettings::SettingsMap::const_iterator mi = map.begin(); mi != map.end(); ++mi) {
		QStringList groups(mi.key().split("/"));
		for (QStringList::iterator it = groups.begin();it!=groups.end();++it) {
			bool ok; QVariant value;
			value.setValue(it->toInt(&ok));
			if (ok) {
				it[1].append('.').append(value.toString());
				groups.erase(it);
			}
		}

		int i; int depth;
		for (depth = 0; (depth < treeGroups.count()) && (depth < (groups.count() - 1)); ++depth) {
			if (treeGroups[depth]!=groups[depth])
				break;
		}

		for (i = treeGroups.count() - 1; i>=depth; --i) {
			xmlWriter.writeEndElement();
			treeGroups.pop_back();
		}

		for (i = depth; i < (groups.count() - 1); ++i) {
			xmlWriter.writeStartElement(groups[i]);
			treeGroups.push_back(groups[i]);
		}

		const QString sValue = mi.value().toString();
		xmlWriter.writeStartElement(groups.last());
		xmlWriter.writeCharacters(sValue);
		xmlWriter.writeEndElement();
	}

	for (int i = 0; i < treeGroups.count(); ++i)
		xmlWriter.writeEndElement();

	xmlWriter.writeEndElement();
	xmlWriter.writeEndDocument();
	return true;
}

