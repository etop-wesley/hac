#ifndef _PROPERTIESSETTINGS_H_
#define _PROPERTIESSETTINGS_H_

#include <hacsettingsglobal.h>
#include <QWidget>

namespace Ui {
    class PropertiesSettings;
}

class HACSETTINGS_EXPORT PropertiesSettings : public QWidget {
    Q_OBJECT
public:
    PropertiesSettings(QWidget *parent = 0);
    ~PropertiesSettings();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_okButton_pressed();
	void on_cancelButton_pressed();

	void on_upButton1_pressed();
	void on_downButton1_pressed();
	void on_upButton2_pressed();
	void on_downButton2_pressed();

private:

private:
    Ui::PropertiesSettings *ui;
};

#endif // _PROPERTIESSETTINGS_H_
