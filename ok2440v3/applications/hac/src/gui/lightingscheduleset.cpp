//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "lightingscheduleset.h"
#include "ui_lightingscheduleset.h"
#include "lightingscheduleitempick.h"

LightingScheduleSet::LightingScheduleSet(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::LightingScheduleSet)
{
	qDebug() << "LightingScheduleSet::LightingScheduleSet";
    ui->setupUi(this);
}

LightingScheduleSet::~LightingScheduleSet()
{
	qDebug() << "LightingScheduleSet::~LightingScheduleSet";
    delete ui;
}

void LightingScheduleSet::changeEvent(QEvent *e)
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

void LightingScheduleSet::on_addButton_clicked()
{
	qDebug() << "LightingScheduleSet::on_addButton_clicked";
	LightingScheduleItemPick *picker = new LightingScheduleItemPick;
	picker->showMaximized();
	if (picker->exec() == QDialog::Accepted) {
		LightingScheduleItemData data = picker->data();
		QString str;
		str += "From:  ";
		str += data.start().toString("hh::mm::ss");
		str += ", To:  ";
		str += data.end().toString("hh::mm::ss");
		str += ", Set: ";
		str += QString::number(data.lighting());
        ui->scheduleListWidget->addItem(str);
	}

	delete picker;
}

void LightingScheduleSet::on_delButton_clicked()
{
	qDebug() << "LightingScheduleSet::on_delButton_clicked" << ui->scheduleListWidget->currentRow();
	if (ui->scheduleListWidget->currentRow() == -1)
		return;

	delete ui->scheduleListWidget->takeItem(ui->scheduleListWidget->currentRow());
}

void LightingScheduleSet::on_editButton_clicked()
{
	qDebug() << "LightingScheduleSet::on_editButton_clicked";
	if (ui->scheduleListWidget->currentRow() == -1)
		return;

	LightingScheduleItemPick *picker = new LightingScheduleItemPick;
	picker->showMaximized();
	if (picker->exec() == QDialog::Accepted) {
		LightingScheduleItemData data = picker->data();
		QString str;
		str += "From:  ";
		str += data.start().toString("hh::mm::ss");
		str += ", To:  ";
		str += data.end().toString("hh::mm::ss");
		str += ", Set: ";
		str += QString::number(data.lighting());
        ui->scheduleListWidget->addItem(str);
	}

	delete picker;
}

void LightingScheduleSet::on_okButton_clicked()
{
	qDebug() << "LightingScheduleSet::on_okButton_clicked";
	close();
}

void LightingScheduleSet::on_cancelButton_clicked()
{
	qDebug() << "LightingScheduleSet::on_cancelButton_clicked";
	close();
}


