#ifndef _HEATINGSETTINGS_H_
#define _HEATINGSETTINGS_H_

#include <QWidget>

namespace Ui {
    class HeatingSettings;
}

class HeatingSettings : public QWidget {
    Q_OBJECT
public:
    HeatingSettings(QWidget *parent = 0);
    ~HeatingSettings();

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
    Ui::HeatingSettings *ui;
};

#endif // _HEATINGSETTINGS_H_
