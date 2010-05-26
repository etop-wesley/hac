#ifndef _LIGHTINGSTAGESELECT_H_
#define _LIGHTINGSTAGESELECT_H_

#include <QWidget>

namespace Ui {
    class LightingStageSelect;
}

class LightingStageSelect : public QWidget {
    Q_OBJECT
public:
    LightingStageSelect(QWidget *parent = 0);
    ~LightingStageSelect();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_returnButton_clicked();

private:

private:
    Ui::LightingStageSelect *ui;
};

#endif // _LIGHTINGSTAGESELECT_H_
