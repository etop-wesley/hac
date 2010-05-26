//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "switchscheduleitempick.h"
#include "ui_switchscheduleitempick.h"

SwitchScheduleItemPick::SwitchScheduleItemPick(QWidget *parent, Qt::WindowFlags f)
:	QDialog(parent, f),
    ui(new Ui::SwitchScheduleItemPick)
{
	qDebug() << "SwitchScheduleItemPick::SwitchScheduleItemPick";
    ui->setupUi(this);
}

SwitchScheduleItemPick::~SwitchScheduleItemPick()
{
	qDebug() << "SwitchScheduleItemPick::~SwitchScheduleItemPick";
    delete ui;
}

void SwitchScheduleItemPick::changeEvent(QEvent *e)
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

void SwitchScheduleItemPick::accept()
{
	qDebug() << "SwitchScheduleItemPick::accept";

	QDialog::accept();
}

void SwitchScheduleItemPick::setData(const SwitchScheduleItemData &data)
{
	if (data == d_data)
		return;

}

SwitchScheduleItemData SwitchScheduleItemPick::SwitchScheduleItemPick::data() const
{
	return d_data;
}

