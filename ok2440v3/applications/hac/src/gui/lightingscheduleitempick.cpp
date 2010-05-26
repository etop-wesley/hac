//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "lightingscheduleitempick.h"
#include "ui_lightingscheduleitempick.h"

LightingScheduleItemPick::LightingScheduleItemPick(QWidget *parent, Qt::WindowFlags f)
:	QDialog(parent, f),
    ui(new Ui::LightingScheduleItemPick)
{
	qDebug() << "LightingScheduleItemPick::LightingScheduleItemPick";
    ui->setupUi(this);
}

LightingScheduleItemPick::~LightingScheduleItemPick()
{
	qDebug() << "LightingScheduleItemPick::~LightingScheduleItemPick";
    delete ui;
}

void LightingScheduleItemPick::changeEvent(QEvent *e)
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

void LightingScheduleItemPick::accept()
{
	qDebug() << "LightingScheduleItemPick::accept";

	QDateTime startDateTime;
	QDateTime endDateTime;
	startDateTime.setTime(QTime(ui->startHourSpinBox->value(), ui->startMinuteSpinBox->value(), ui->startSecondSpinBox->value()));
	endDateTime.setTime(QTime(ui->endHourSpinBox->value(), ui->endMinuteSpinBox->value(), ui->endSecondSpinBox->value()));
	int lighting = ui->listNavigator->value();
	d_data.setStart(startDateTime);
	d_data.setEnd(endDateTime);
	d_data.setLighting(lighting);
	QDialog::accept();
}

void LightingScheduleItemPick::setData(const LightingScheduleItemData &data)
{
	if (data == d_data)
		return;

	d_data = data;
	QTime startTime = d_data.start().time();
	QTime endTime = d_data.end().time();
	ui->startHourSpinBox->setValue(startTime.hour());
	ui->startMinuteSpinBox->setValue(startTime.minute());
	ui->startSecondSpinBox->setValue(startTime.second());
	ui->endHourSpinBox->setValue(endTime.hour());
	ui->endMinuteSpinBox->setValue(endTime.minute());
	ui->endSecondSpinBox->setValue(endTime.second());
	ui->listNavigator->setValue(d_data.lighting());
}

LightingScheduleItemData LightingScheduleItemPick::data() const
{
	return d_data;
}

