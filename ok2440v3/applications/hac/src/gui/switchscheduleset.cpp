//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "switchscheduleset.h"
#include "ui_switchscheduleset.h"
#include "switchscheduleitempick.h"

SwitchScheduleSet::SwitchScheduleSet(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::SwitchScheduleSet)
{
	qDebug() << "SwitchScheduleSet::SwitchScheduleSet";
    ui->setupUi(this);
}

SwitchScheduleSet::~SwitchScheduleSet()
{
	qDebug() << "SwitchScheduleSet::~SwitchScheduleSet";
    delete ui;
}

void SwitchScheduleSet::changeEvent(QEvent *e)
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

void SwitchScheduleSet::on_addButton_clicked()
{
	qDebug() << "SwitchScheduleSet::on_addButton_clicked";
	SwitchScheduleItemPick *picker = new SwitchScheduleItemPick;
	picker->showMaximized();
	if (picker->exec() == QDialog::Accepted) {
		SwitchScheduleItemData data = picker->data();
		QString str;
		str += "From:  ";
		str += data.start().toString("hh::mm::ss");
		str += ", To:  ";
		str += data.end().toString("hh::mm::ss");
		str += ", Set: ";
		str += QString::number(data.status());
        ui->scheduleListWidget->addItem(str);
	}

	delete picker;
}

void SwitchScheduleSet::on_delButton_clicked()
{
	qDebug() << "SwitchScheduleSet::on_delButton_clicked" << ui->scheduleListWidget->currentRow();
	if (ui->scheduleListWidget->currentRow() == -1)
		return;

	delete ui->scheduleListWidget->takeItem(ui->scheduleListWidget->currentRow());
}

void SwitchScheduleSet::on_editButton_clicked()
{
	qDebug() << "SwitchScheduleSet::on_editButton_clicked";
	if (ui->scheduleListWidget->currentRow() == -1)
		return;

	SwitchScheduleItemPick *picker = new SwitchScheduleItemPick;
	picker->showMaximized();
	if (picker->exec() == QDialog::Accepted) {
		SwitchScheduleItemData data = picker->data();
		QString str;
		str += "From:  ";
		str += data.start().toString("hh::mm::ss");
		str += ", To:  ";
		str += data.end().toString("hh::mm::ss");
		str += ", Set: ";
		str += QString::number(data.status());
        ui->scheduleListWidget->addItem(str);
	}

	delete picker;
}

void SwitchScheduleSet::on_okButton_clicked()
{
	qDebug() << "SwitchScheduleSet::on_okButton_clicked";
	close();
}

void SwitchScheduleSet::on_cancelButton_clicked()
{
	qDebug() << "SwitchScheduleSet::on_cancelButton_clicked";
	close();
}


