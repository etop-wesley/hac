//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "stagesettingspage.h"
#include "ui_stagesettingspage.h"
#include "acscheduleset.h"
#include "gui.h"

StageSettingsPage::StageSettingsPage(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::StageSettingsPage)
{
	qDebug() << "StageSettingsPage::StageSettingsPage";
    ui->setupUi(this);

	ui->stackedWidget->setContentsMargins(0, 0, 0, 0);
/*
	((AirConditioningControlPage *)(ui->stackedWidget->widget(0)))->setBeUsedInStage();
	((HeatingControlPage *)(ui->stackedWidget->widget(1)))->setBeUsedInStage();
	((SimulateHomeSettings *)(ui->stackedWidget->widget(2)))->setBeUsedInStage();
	//((CurtainsControlPage *)(ui->stackedWidget->widget(3)))->setBeUsedInStage();
	((SwitchControlPage *)(ui->stackedWidget->widget(3)))->setBeUsedInStage();
*/
	d_lightOnTime = QTime(12, 30);
	d_lightOffTime = QTime(18, 45);

	ui->lightOnHourLineEdit2->setText(d_lightOnTime.toString("hh"));
	ui->lightOnMinuteLineEdit2->setText(d_lightOnTime.toString("mm"));
	ui->lightOffHourLineEdit2->setText(d_lightOffTime.toString("hh"));
	ui->lightOffMinuteLineEdit2->setText(d_lightOffTime.toString("mm"));
on_lightOffButton_pressed();
}

StageSettingsPage::~StageSettingsPage()
{
	qDebug() << "StageSettingsPage::~StageSettingsPage";
    delete ui;
}

void StageSettingsPage::changeEvent(QEvent *e)
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

void StageSettingsPage::on_acButton_pressed()
{
	ui->stackedWidget->setCurrentIndex(0);
}

void StageSettingsPage::on_heatingButton_pressed()
{
	ui->stackedWidget->setCurrentIndex(1);
}

void StageSettingsPage::on_lightButton_pressed()
{
	ui->stackedWidget->setCurrentIndex(2);
}

void StageSettingsPage::on_switchButton_pressed()
{
	ui->stackedWidget->setCurrentIndex(3);
}
/*
void StageSettingsPage::on_curtainsButton_pressed()
{
	ui->stackedWidget->setCurrentIndex(4);
}*/


static int set = 27;            // FIXME!
static int set2 = 27;            // FIXME!

void StageSettingsPage::on_tempUpButton_pressed()
{
	ui->tempSetLabel->setText(QString::number(++set));
}

void StageSettingsPage::on_tempDownButton_pressed()
{
	ui->tempSetLabel->setText(QString::number(--set));
}

void StageSettingsPage::on_tempUpButton2_pressed()
{
	ui->tempSetLabel2->setText(QString::number(++set2));
}

void StageSettingsPage::on_tempDownButton2_pressed()
{
	ui->tempSetLabel2->setText(QString::number(--set2));
}



void StageSettingsPage::on_lightUpButton_pressed()
{
	if (focusWidget() == ui->lightOnHourLineEdit2) {
		d_lightOnTime.setHMS(d_lightOnTime.hour() < 23 ? d_lightOnTime.hour() + 1 : d_lightOnTime.hour(), d_lightOnTime.minute(), 0);
		ui->lightOnHourLineEdit2->setText(d_lightOnTime.toString("hh"));
	} else if (focusWidget() == ui->lightOnMinuteLineEdit2) {
		d_lightOnTime.setHMS(d_lightOnTime.hour(), d_lightOnTime.minute() < 59 ? d_lightOnTime.minute() + 1 : d_lightOnTime.minute(), 0);
		ui->lightOnMinuteLineEdit2->setText(d_lightOnTime.toString("mm"));
	} else if (focusWidget() == ui->lightOffHourLineEdit2) {
		d_lightOnTime.setHMS(d_lightOffTime.hour() < 23 ? d_lightOffTime.hour() + 1 : d_lightOffTime.hour(), d_lightOffTime.minute(), 0);
		ui->lightOffHourLineEdit2->setText(d_lightOffTime.toString("hh"));
	} else if (focusWidget() == ui->lightOffMinuteLineEdit2) {
		d_lightOnTime.setHMS(d_lightOffTime.hour(), d_lightOffTime.minute() < 59 ? d_lightOffTime.minute() + 1 : d_lightOffTime.minute(), 0);
		ui->lightOffMinuteLineEdit2->setText(d_lightOffTime.toString("mm"));
	}
}

void StageSettingsPage::on_lightDownButton_pressed()
{
	if (focusWidget() == ui->lightOnHourLineEdit2) {
		d_lightOnTime.setHMS(d_lightOnTime.hour() > 0 ? d_lightOnTime.hour() - 1 : d_lightOnTime.hour(), d_lightOnTime.minute(), 0);
		ui->lightOnHourLineEdit2->setText(d_lightOnTime.toString("hh"));
	} else if (focusWidget() == ui->lightOnMinuteLineEdit2) {
		d_lightOnTime.setHMS(d_lightOnTime.hour(), d_lightOnTime.minute() > 0 ? d_lightOnTime.minute() - 1 : d_lightOnTime.minute(), 0);
		ui->lightOnMinuteLineEdit2->setText(d_lightOnTime.toString("mm"));
	} else if (focusWidget() == ui->lightOffHourLineEdit2) {
		d_lightOnTime.setHMS(d_lightOffTime.hour() > 0 ? d_lightOffTime.hour() - 1 : d_lightOffTime.hour(), d_lightOffTime.minute(), 0);
		ui->lightOffHourLineEdit2->setText(d_lightOffTime.toString("hh"));
	} else if (focusWidget() == ui->lightOffMinuteLineEdit2) {
		d_lightOnTime.setHMS(d_lightOffTime.hour(), d_lightOffTime.minute() > 0 ? d_lightOffTime.minute() - 1 : d_lightOffTime.minute(), 0);
		ui->lightOffMinuteLineEdit2->setText(d_lightOffTime.toString("mm"));
	}
}


void StageSettingsPage::on_numUpButton_pressed()
{
	int num = ui->lcdNumber->value() + 1;
	if (num > 6)
		num = 1;
	ui->lcdNumber->display("0"+QString::number(num));
}

void StageSettingsPage::on_numDownButton_pressed()
{
	int num = ui->lcdNumber->value() - 1;
	if (num < 1)
		num = 6;
	ui->lcdNumber->display("0"+QString::number(num));
}

void StageSettingsPage::on_lightOnButton_pressed()
{
	ui->lightPixmapLabel->setPixmap(QPixmap(":/Hac/switch-on.png"));
}

void StageSettingsPage::on_lightOffButton_pressed()
{
	ui->lightPixmapLabel->setPixmap(QPixmap(":/Hac/switch-off.png"));
}


