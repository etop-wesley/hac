//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QTime>
#include "simulatehomesettings.h"
#include "ui_simulatehomesettings.h"
#include "gui.h"

SimulateHomeSettings::SimulateHomeSettings(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::SimulateHomeSettings)
{
	qDebug() << "SimulateHomeSettings::SimulateHomeSettings";
    ui->setupUi(this);

	d_lightOnTime = QTime(12, 30);
	d_lightOffTime = QTime(18, 45);

	ui->lightOnHourLineEdit->setText(d_lightOnTime.toString("hh"));
	ui->lightOnMinuteLineEdit->setText(d_lightOnTime.toString("mm"));
	ui->lightOffHourLineEdit->setText(d_lightOffTime.toString("hh"));
	ui->lightOffMinuteLineEdit->setText(d_lightOffTime.toString("mm"));
}

SimulateHomeSettings::~SimulateHomeSettings()
{
	qDebug() << "SimulateHomeSettings::~SimulateHomeSettings";
    delete ui;
}

void SimulateHomeSettings::changeEvent(QEvent *e)
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

void SimulateHomeSettings::setBeUsedInStage()
{
	ui->titleLabel->hide();
	ui->frame_1->hide();
}

void SimulateHomeSettings::on_upButton_pressed()
{
	if (focusWidget() == ui->lightOnHourLineEdit) {
		d_lightOnTime.setHMS(d_lightOnTime.hour() < 23 ? d_lightOnTime.hour() + 1 : d_lightOnTime.hour(), d_lightOnTime.minute(), 0);
		ui->lightOnHourLineEdit->setText(d_lightOnTime.toString("hh"));
	} else if (focusWidget() == ui->lightOnMinuteLineEdit) {
		d_lightOnTime.setHMS(d_lightOnTime.hour(), d_lightOnTime.minute() < 59 ? d_lightOnTime.minute() + 1 : d_lightOnTime.minute(), 0);
		ui->lightOnMinuteLineEdit->setText(d_lightOnTime.toString("mm"));
	} else if (focusWidget() == ui->lightOffHourLineEdit) {
		d_lightOnTime.setHMS(d_lightOffTime.hour() < 23 ? d_lightOffTime.hour() + 1 : d_lightOffTime.hour(), d_lightOffTime.minute(), 0);
		ui->lightOffHourLineEdit->setText(d_lightOffTime.toString("hh"));
	} else if (focusWidget() == ui->lightOffMinuteLineEdit) {
		d_lightOnTime.setHMS(d_lightOffTime.hour(), d_lightOffTime.minute() < 59 ? d_lightOffTime.minute() + 1 : d_lightOffTime.minute(), 0);
		ui->lightOffMinuteLineEdit->setText(d_lightOffTime.toString("mm"));
	}
}

void SimulateHomeSettings::on_downButton_pressed()
{
	if (focusWidget() == ui->lightOnHourLineEdit) {
		d_lightOnTime.setHMS(d_lightOnTime.hour() > 0 ? d_lightOnTime.hour() - 1 : d_lightOnTime.hour(), d_lightOnTime.minute(), 0);
		ui->lightOnHourLineEdit->setText(d_lightOnTime.toString("hh"));
	} else if (focusWidget() == ui->lightOnMinuteLineEdit) {
		d_lightOnTime.setHMS(d_lightOnTime.hour(), d_lightOnTime.minute() > 0 ? d_lightOnTime.minute() - 1 : d_lightOnTime.minute(), 0);
		ui->lightOnMinuteLineEdit->setText(d_lightOnTime.toString("mm"));
	} else if (focusWidget() == ui->lightOffHourLineEdit) {
		d_lightOnTime.setHMS(d_lightOffTime.hour() > 0 ? d_lightOffTime.hour() - 1 : d_lightOffTime.hour(), d_lightOffTime.minute(), 0);
		ui->lightOffHourLineEdit->setText(d_lightOffTime.toString("hh"));
	} else if (focusWidget() == ui->lightOffMinuteLineEdit) {
		d_lightOnTime.setHMS(d_lightOffTime.hour(), d_lightOffTime.minute() > 0 ? d_lightOffTime.minute() - 1 : d_lightOffTime.minute(), 0);
		ui->lightOffMinuteLineEdit->setText(d_lightOffTime.toString("mm"));
	}
}


