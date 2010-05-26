#include "hackeyboarddriverplugin.h"

QStringList HacKeyboardDriverPlugin::keys() const
{
        return QStringList() << "ArmSys2440Kbd";
}

QWSKeyboardHandler* HacKeyboardDriverPlugin::create(const QString& key,const QString &device)
{
        if(key.toLower() == "armsys2440kbd")
                return new ArmSys2440KeyboardHandler(device);
        return 0;
}

HacKeyboardDriverPlugin::HacKeyboardDriverPlugin()
: QKbdDriverPlugin()
{

}

Q_EXPORT_PLUGIN2(hackbd,HacKeyboardDriverPlugin)

