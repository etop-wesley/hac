//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "hacscreensaverchannel.h"

static const char *SSAVER_CHANNEL_NAME = "Service/ScreenSaver";
static const char *SEND_CMD_DATA_REQUEST = "SSaver/requestData";
static const char *SEND_CMD_DATA_REPLY = "SSaver/replyData";
static const char *SEND_CMD_DATA_COMMIT = "SSaver/commitData";
static const char *SEND_CMD_PREVIEW = "SSaver/preview";
static const char *SEND_CMD_ENABLE = "SSaver/enable";

#define SSAVER_PLUGIN_DIR  "/media/ext/.osd-extended/programs/Qtopia/plugins/ssaver/"
#define SSAVER_PLUGIN_LINK_DIR  "/etc/ssaverplugins/"
#define SYSTEM_CONFIG     "/media/ext/data/sysconfig.ini"

#define INTERVAL_FIELD    "ssaver/interval"
#define NAME_FIELD           "ssaver/name"
#define DEFAULT_INTERVAL   30
#define INVALID_SSAVER     "NULL"

#define MINUTE(X)   ((X) * 1000 *60 )

NSSaverServer::NSSaverServer( QObject *parent)
:QCopChannel(SSAVER_CHANNEL_NAME,parent)
{
	loadConfigure( );
	reloadScreenSaverPlugin ( );
	QWSServer :: setScreenSaverInterval(MINUTE(interval));
}

NSSaverServer::~NSSaverServer()
{

}

const QStringList NSSaverServer :: getSSaverName ( ) const
{
    QDir pluginsDir = QDir(SSAVER_PLUGIN_LINK_DIR);
	QStringList list;

    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
    {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (plugin)
		{
			QWSScreenSaver *ssaverplugin = dynamic_cast<QWSScreenSaver *>(plugin);
			if (NULL != ssaverplugin)
			{
				list<<plugin->objectName( );
			}
		}
	}

	return list;
}

void NSSaverServer :: loadConfigure ( )
{
	QSettings settings(SYSTEM_CONFIG,QSettings::IniFormat);
	interval = settings.value(INTERVAL_FIELD, DEFAULT_INTERVAL).toInt( );
	ssaver = settings.value (NAME_FIELD , INVALID_SSAVER).toString( );
	
}

void NSSaverServer :: saveConfigure ( )
{
	QSettings settings(SYSTEM_CONFIG,QSettings::IniFormat);
	settings.setValue(INTERVAL_FIELD, interval );

	if ( ssaver != INVALID_SSAVER)
		settings.setValue(NAME_FIELD, ssaver );
}

void NSSaverServer :: receive(const QString &msg, const QByteArray &data)
{
	QDataStream in(data);
    if ( msg == SEND_CMD_DATA_REQUEST )
	{
		QByteArray dataArray;
		QDataStream out(&dataArray, QIODevice::WriteOnly);

		out << getSSaverName ( ) << ssaver << interval;

		QCopChannel::send(SSAVER_CHANNEL_NAME, 
								 SEND_CMD_DATA_REPLY , dataArray);
		
	}
	else if ( msg == SEND_CMD_DATA_COMMIT )
	{
		QString tmpssaver;
		in >> interval >> tmpssaver;

		if ( tmpssaver != ssaver)
		{
			ssaver = tmpssaver;
			reloadScreenSaverPlugin ( );
		}

		QWSServer :: setScreenSaverInterval(MINUTE(interval));
		saveConfigure ( );
	}
	else if ( msg == SEND_CMD_PREVIEW )
	{
		/*  fix me */
		qDebug() << "preview ";

	}
	else if ( msg == SEND_CMD_ENABLE )
	{
		bool enable;
		in >> enable;
		if (enable == true) 
		{
			reloadScreenSaverPlugin ( );
			QWSServer::setScreenSaverInterval(MINUTE(interval));
		}
		else 
		{
			QWSServer::setScreenSaver(NULL);
		}
	}
}

bool NSSaverServer :: reloadScreenSaverPlugin ( )
{
	QDir pluginsDir = QDir(SSAVER_PLUGIN_LINK_DIR);
	QWSServer::setScreenSaver(NULL);

    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
    {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (plugin)
		{
			if ( ssaver == INVALID_SSAVER )
			{
				QWSScreenSaver *ssaverplugin = dynamic_cast<QWSScreenSaver *>(plugin);
				if ( ssaverplugin )
				{
					qDebug()<<"Append qws screen saver "<< fileName;
					QWSServer::setScreenSaver( ssaverplugin );
					ssaver = plugin->objectName( );
					return true;
                } 
				else
				{
					qDebug()<<"Isn't qws screen saver "<<fileName;
					delete plugin;
				}
				
			}
			else if ( plugin->objectName( ) == ssaver )
			{
				QWSScreenSaver *ssaverplugin = dynamic_cast<QWSScreenSaver *>(plugin);
				if ( ssaverplugin )
				{
					qDebug()<<"Append qws screen saver "<<fileName ;
					QWSServer::setScreenSaver( ssaverplugin );
                    return true;
                } 
				else
				{
					qDebug()<<"Isn't qws screen saver "<<fileName;
					delete plugin;
				}
			}
		}
	}
	ssaver = INVALID_SSAVER;
	return false;
}

NSSaverClient::NSSaverClient( QObject *parent)
:	QObject(parent)
{
	channel = new QCopChannel(SSAVER_CHANNEL_NAME);

	connect(channel, SIGNAL(received (const QString &, const QByteArray &)),
			this, SLOT(onReceive(const QString &, const QByteArray&)));
}

NSSaverClient::~NSSaverClient()
{
	/* FIX ME: Should delete chanenl here. But it will result
		in copchannel communicate failed.*/
	//delete channel;
}

void NSSaverClient :: fetchData ( )
{
	QCopChannel :: send ( SSAVER_CHANNEL_NAME, SEND_CMD_DATA_REQUEST );
}

void NSSaverClient :: onReceive(const QString &msg, const QByteArray &data)
{
	QDataStream in(data);

	if ( msg == SEND_CMD_DATA_REPLY )
	{
		QStringList list;
		QString currentSSaver;
		int interval;
		in >> list >> currentSSaver >> interval ;
		emit getNames ( list );
		emit getCurrentSSaver(currentSSaver, interval);
	}
}


void NSSaverClient :: commitData ( const QString &ssaver , int interval )
{
	QByteArray dataArray;
	QDataStream out(&dataArray, QIODevice::WriteOnly);

	out << interval << ssaver ;

	QCopChannel::send(SSAVER_CHANNEL_NAME, 
							 SEND_CMD_DATA_COMMIT , dataArray);
}

void NSSaverClient :: preview ( )
{
	QCopChannel :: send ( SSAVER_CHANNEL_NAME, SEND_CMD_PREVIEW );
}

void NSSaverClient :: enable ( bool isEnabled )
{
	QByteArray dataArray;
	QDataStream out(&dataArray, QIODevice::WriteOnly);

	out << isEnabled ;

	QCopChannel::send(SSAVER_CHANNEL_NAME, SEND_CMD_ENABLE, dataArray);
}
