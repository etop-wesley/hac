#ifndef _REGIONALSETTINGS_H_
#define _REGIONALSETTINGS_H_

#include <QWidget>

namespace Ui {
    class RegionalSettings;
}

class RegionalSettings : public QWidget {
    Q_OBJECT
public:
    RegionalSettings(QWidget *parent = 0);
    ~RegionalSettings();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_okButton_pressed();
	void on_cancelButton_pressed();

private:

private:
    Ui::RegionalSettings *ui;
};

#endif // _REGIONALSETTINGS_H_
