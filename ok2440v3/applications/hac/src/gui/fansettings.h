#ifndef _FANSETTINGS_H_
#define _FANSETTINGS_H_

#include <QWidget>

namespace Ui {
    class FanSettings;
}

class FanSettings : public QWidget {
    Q_OBJECT
public:
    FanSettings(QWidget *parent = 0);
    ~FanSettings();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_okButton_clicked();
	void on_cancelButton_clicked();
	void on_unitComboBox_currentIndexChanged(int);
	void on_minComboBox_currentIndexChanged(int);
	void on_maxComboBox_currentIndexChanged(int);

private:

private:
    Ui::FanSettings *ui;
};

#endif // _FANSETTINGS_H_
