//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "acscheduleset.h"
#include "ui_acscheduleset.h"
#include <QListWidgetItem>

AcScheduleSet::AcScheduleSet(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::AcScheduleSet)
{
	qDebug() << "AcScheduleSet::AcScheduleSet";
    ui->setupUi(this);
}

AcScheduleSet::~AcScheduleSet()
{
	qDebug() << "AcScheduleSet::~AcScheduleSet";
    delete ui;
}

void AcScheduleSet::changeEvent(QEvent *e)
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

void AcScheduleSet::setTitle(const QString &text)
{
	ui->titleLabel->setText(text);
}


void AcScheduleSet::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    ui->picker->setPickedList(QList<HacAnalogClockPickWidget::PickedItemData>());
}



