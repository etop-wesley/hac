//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "mainswitchpage.h"
#include "ui_mainswitchpage.h"
#include "switchscheduleitempick.h"
#include "switchscheduledelaypick.h"

MainSwitchPage::MainSwitchPage(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::MainSwitchPage)
{
	qDebug() << "MainSwitchPage::MainSwitchPage";
    ui->setupUi(this);
}

MainSwitchPage::~MainSwitchPage()
{
	qDebug() << "MainSwitchPage::~MainSwitchPage";
    delete ui;
}

void MainSwitchPage::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainSwitchPage::on_startButton_clicked()
{
	qDebug() << "MainSwitchPage::on_startButton_clicked";

}

void MainSwitchPage::on_stopButton_clicked()
{
	qDebug() << "MainSwitchPage::on_stopButton_clicked";

}

void MainSwitchPage::on_scheduleButton_clicked()
{
	qDebug() << "MainSwitchPage::on_scheduleButton_clicked";
	int value = ui->modeComboBox->currentIndex();
	if (value == 1) {
		SwitchScheduleItemPick *w = new SwitchScheduleItemPick;
		w->setAttribute(Qt::WA_DeleteOnClose, true);
		w->showMaximized();
	} else if (value == 2) {
		SwitchScheduleDelayPick *w = new SwitchScheduleDelayPick;
		w->setAttribute(Qt::WA_DeleteOnClose, true);
		w->showMaximized();
	}
}
