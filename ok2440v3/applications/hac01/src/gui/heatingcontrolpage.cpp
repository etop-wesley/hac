//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "heatingcontrolpage.h"
#include "ui_heatingcontrolpage.h"
#include "hacapplication.h"
#include "gui.h"

HeatingControlPage::HeatingControlPage(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::HeatingControlPage)
{
	qDebug() << "HeatingControlPage::HeatingControlPage";
    ui->setupUi(this);
}

HeatingControlPage::~HeatingControlPage()
{
	qDebug() << "HeatingControlPage::~HeatingControlPage";
    delete ui;
}

void HeatingControlPage::changeEvent(QEvent *e)
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

void HeatingControlPage::setBeUsedInStage()
{
	ui->titleLabel->hide();
	ui->frame_1->hide();
}


void HeatingControlPage::on_scheduleButton_pressed()
{
	qDebug() << "HeatingControlPage::on_scheduleButton_pressed";
	HacApp->showWindow("HeatingScheduleSet");
}


static int set = 27;            // FIXME!

void HeatingControlPage::on_tempUpButton_pressed()
{
	ui->tempSetLabel->setText(QString::number(++set));
}

void HeatingControlPage::on_tempDownButton_pressed()
{
	ui->tempSetLabel->setText(QString::number(--set));
}


