//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "fanscheduleitempick.h"
#include "ui_fanscheduleitempick.h"

FanScheduleItemPick::FanScheduleItemPick(QWidget *parent, Qt::WindowFlags f)
:	QDialog(parent, f),
    ui(new Ui::FanScheduleItemPick)
{
	qDebug() << "FanScheduleItemPick::FanScheduleItemPick";
    ui->setupUi(this);
}

FanScheduleItemPick::~FanScheduleItemPick()
{
	qDebug() << "FanScheduleItemPick::~FanScheduleItemPick";
    delete ui;
}

void FanScheduleItemPick::changeEvent(QEvent *e)
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

void FanScheduleItemPick::accept()
{
	qDebug() << "FanScheduleItemPick::accept";

	QDateTime startDateTime;
	QDateTime endDateTime;
	startDateTime.setTime(QTime(ui->startHourSpinBox->value(), ui->startMinuteSpinBox->value(), ui->startSecondSpinBox->value()));
	endDateTime.setTime(QTime(ui->endHourSpinBox->value(), ui->endMinuteSpinBox->value(), ui->endSecondSpinBox->value()));
	int temperature = ui->temperatureSpinBox->value();
	d_data.setStart(startDateTime);
	d_data.setEnd(endDateTime);
	d_data.setTemperature(temperature);
	QDialog::accept();
}

void FanScheduleItemPick::setData(const FanScheduleItemData &data)
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
	ui->temperatureSpinBox->setValue(d_data.temperature());
}

FanScheduleItemData FanScheduleItemPick::data() const
{
	return d_data;
}

