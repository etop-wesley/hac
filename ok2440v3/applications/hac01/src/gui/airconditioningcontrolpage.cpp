//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "airconditioningcontrolpage.h"
#include "ui_airconditioningcontrolpage.h"
#include "hacapplication.h"
#include "gui.h"

AirConditioningControlPage::AirConditioningControlPage(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::AirConditioningControlPage)
{
	qDebug() << "AirConditioningControlPage::AirConditioningControlPage";
    ui->setupUi(this);
}

AirConditioningControlPage::~AirConditioningControlPage()
{
	qDebug() << "AirConditioningControlPage::~AirConditioningControlPage";
    delete ui;
}

void AirConditioningControlPage::changeEvent(QEvent *e)
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

void AirConditioningControlPage::setBeUsedInStage()
{
	ui->titleLabel->hide();
	ui->frame_1->hide();
}


void AirConditioningControlPage::on_scheduleButton_pressed()
{
	qDebug() << "AirConditioningControlPage::on_scheduleButton_pressed";
	HacApp->showWindow("AcScheduleSet");
}


static int set = 27;            // FIXME!

void AirConditioningControlPage::on_tempUpButton_pressed()
{
	ui->tempSetLabel->setText(QString::number(++set));
}

void AirConditioningControlPage::on_tempDownButton_pressed()
{
	ui->tempSetLabel->setText(QString::number(--set));
}


