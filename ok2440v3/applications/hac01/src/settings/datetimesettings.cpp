//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "datetimesettings.h"
#include "ui_datetimesettings.h"
#include "gui.h"
#include <QCalendarWidget>


/*
 *  //FIXME: system tiem changed cause QTimer not timeout ?!!!
 */
DateTimeSettings::DateTimeSettings(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::DateTimeSettings)
{
	qDebug() << "DateTimeSettings::DateTimeSettings";
    ui->setupUi(this);

    QDateTime datetime = QDateTime::currentDateTime();
	if (datetime.date().year() == 1970) { //FIXME : hwclock -w not work ?
		ui->monthSpinBox->setValue(4);
		ui->daySpinBox->setValue(7);
		ui->yearSpinBox->setValue(2010);
		ui->hourSpinBox->setValue(12);
		ui->minuteSpinBox->setValue(0);
		ui->secondSpinBox->setValue(0);
	} else  {
		ui->monthSpinBox->setValue(datetime.date().month());
		ui->daySpinBox->setValue(datetime.date().day());
		ui->yearSpinBox->setValue(datetime.date().year());
		ui->hourSpinBox->setValue(datetime.time().hour());
		ui->minuteSpinBox->setValue(datetime.time().minute());
		ui->secondSpinBox->setValue(datetime.time().second());
	}
}

DateTimeSettings::~DateTimeSettings()
{
	qDebug() << "DateTimeSettings::~DateTimeSettings";
    delete ui;
}

void DateTimeSettings::changeEvent(QEvent *e)
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

void DateTimeSettings::on_downButton_pressed()
{

}


void DateTimeSettings::on_okButton_pressed()
{
	int month = ui->monthSpinBox->value();
	int day = ui->daySpinBox->value();
	int year = ui->yearSpinBox->value();
	int hour = ui->hourSpinBox->value();
	int minute = ui->minuteSpinBox->value();
	int second = ui->secondSpinBox->value();

	QString MM = (month >= 10 ? QString::number(month) : "0" + QString::number(month));
	QString DD = (month >= 10 ? QString::number(day) : "0" + QString::number(day));
	QString CCYY = (year >= 10 ? QString::number(year) : "0" + QString::number(year));
	QString hh = (hour >= 10 ? QString::number(hour) : "0" + QString::number(hour));
	QString mm = (minute >= 10 ? QString::number(minute) : "0" + QString::number(minute));
	QString ss = (second >= 10 ? QString::number(second) : "0" + QString::number(second));

	QString date;

	//date --help says: Usage: date [OPTION]... [MMDDhhmm[[CC]YY][.ss]] [+FORMAT]
	date.sprintf("date -s \"%s%s%s%s%s.%s\"", 
				 MM.toAscii().constData(),
				 DD.toAscii().constData(),
				 hh.toAscii().constData(),
				 mm.toAscii().constData(),
				 CCYY.toAscii().constData(),
				 ss.toAscii().constData());
	qDebug() << date;
	system(date.toAscii().constData());
	system("hwclock -w");
	system("hwclock -u");
	close();
}

void DateTimeSettings::on_cancelButton_pressed()
{
	close();
}

