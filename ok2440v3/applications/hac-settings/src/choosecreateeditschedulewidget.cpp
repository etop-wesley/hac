//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "choosecreateeditschedulewidget.h"
#include "ui_choosecreateeditschedulewidget.h"

ChooseCreateEditScheduleWidget::ChooseCreateEditScheduleWidget(QWidget *parent)
:	QWidget(parent), ui(new Ui::ChooseCreateEditScheduleWidget)
{
	qDebug() << "ChooseCreateEditScheduleWidget::ChooseCreateEditScheduleWidget";
    ui->setupUi(this);
}

ChooseCreateEditScheduleWidget::~ChooseCreateEditScheduleWidget()
{
	qDebug() << "ChooseCreateEditScheduleWidget::~ChooseCreateEditScheduleWidget";
    delete ui;
}

void ChooseCreateEditScheduleWidget::changeEvent(QEvent *e)
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

void ChooseCreateEditScheduleWidget::on_backButton_pressed()
{
	qDebug() << "ChooseCreateEditScheduleWidget::on_backButton_pressed";
	emit back();
}

void ChooseCreateEditScheduleWidget::on_helpButton_pressed()
{
	qDebug() << "ChooseCreateEditScheduleWidget::on_helpButton_pressed";
	emit help();
}




