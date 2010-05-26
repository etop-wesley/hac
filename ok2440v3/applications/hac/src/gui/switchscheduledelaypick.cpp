//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "switchscheduledelaypick.h"
#include "ui_switchscheduledelaypick.h"

SwitchScheduleDelayPick::SwitchScheduleDelayPick(QWidget *parent, Qt::WindowFlags f)
:	QDialog(parent, f),
    ui(new Ui::SwitchScheduleDelayPick)
{
	qDebug() << "SwitchScheduleDelayPick::SwitchScheduleDelayPick";
    ui->setupUi(this);
}

SwitchScheduleDelayPick::~SwitchScheduleDelayPick()
{
	qDebug() << "SwitchScheduleDelayPick::~SwitchScheduleDelayPick";
    delete ui;
}

void SwitchScheduleDelayPick::changeEvent(QEvent *e)
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

void SwitchScheduleDelayPick::accept()
{
	qDebug() << "SwitchScheduleDelayPick::accept";

	QDialog::accept();
}

void SwitchScheduleDelayPick::setData(const SwitchScheduleDelayData &data)
{
	if (data == d_data)
		return;

}

SwitchScheduleDelayData SwitchScheduleDelayPick::data() const
{
	return d_data;
}

