//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "fanscheduleset.h"
#include "ui_fanscheduleset.h"
#include "fanscheduleitempick.h"

FanScheduleSet::FanScheduleSet(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::FanScheduleSet)
{
	qDebug() << "FanScheduleSet::FanScheduleSet";
    ui->setupUi(this);
}

FanScheduleSet::~FanScheduleSet()
{
	qDebug() << "FanScheduleSet::~FanScheduleSet";
    delete ui;
}

void FanScheduleSet::changeEvent(QEvent *e)
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

void FanScheduleSet::on_addButton_clicked()
{
	qDebug() << "FanScheduleSet::on_addButton_clicked";
	FanScheduleItemPick *picker = new FanScheduleItemPick;
	picker->showMaximized();
	if (picker->exec() == QDialog::Accepted) {
		FanScheduleItemData data = picker->data();
		QString str;
		str += "From:  ";
		str += data.start().toString("hh::mm::ss");
		str += ", To:  ";
		str += data.end().toString("hh::mm::ss");
		str += ", Set: ";
		str += QString::number(data.temperature());
        ui->scheduleListWidget->addItem(str);
	}

	delete picker;
}

void FanScheduleSet::on_delButton_clicked()
{
	qDebug() << "FanScheduleSet::on_delButton_clicked" << ui->scheduleListWidget->currentRow();
	if (ui->scheduleListWidget->currentRow() == -1)
		return;

	delete ui->scheduleListWidget->takeItem(ui->scheduleListWidget->currentRow());
}

void FanScheduleSet::on_editButton_clicked()
{
	qDebug() << "FanScheduleSet::on_editButton_clicked";
	if (ui->scheduleListWidget->currentRow() == -1)
		return;

	FanScheduleItemPick *picker = new FanScheduleItemPick;
	picker->showMaximized();
	if (picker->exec() == QDialog::Accepted) {
		FanScheduleItemData data = picker->data();
		QString str;
		str += "From:  ";
		str += data.start().toString("hh::mm::ss");
		str += ", To:  ";
		str += data.end().toString("hh::mm::ss");
		str += ", Set: ";
		str += QString::number(data.temperature());
        ui->scheduleListWidget->addItem(str);
	}

	delete picker;
}

void FanScheduleSet::on_okButton_clicked()
{
	qDebug() << "FanScheduleSet::on_okButton_clicked";
	close();
}

void FanScheduleSet::on_cancelButton_clicked()
{
	qDebug() << "FanScheduleSet::on_cancelButton_clicked";
	close();
}


