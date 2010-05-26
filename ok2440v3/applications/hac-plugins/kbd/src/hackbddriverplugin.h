/*
 * mtk168_2.0 keyboard driver plugin header 
 *  
 * @author: wesley.xie elelonger@gmail.com 
 *  
 */

#ifndef _MKBDDRIVERPLUGIN_H_
#define _MKBDDRIVERPLUGIN_H__


#include <QStringList>
#include <QString>

#include <QKbdDriverPlugin>
#include <QWSKeyboardHandler>


class HacKbdDriverPlugin: public QKbdDriverPlugin {
	Q_OBJECT

public:
	HacKbdDriverPlugin (QObject * parent = 0);
	~HacKbdDriverPlugin ();

	virtual QWSKeyboardHandler * create ( const QString &key, const QString & device);
	virtual QStringList keys () const;

};

#endif //_MKBDDRIVERPLUGIN_H_
