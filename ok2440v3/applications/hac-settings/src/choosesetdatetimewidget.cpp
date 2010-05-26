//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "choosesetdatetimewidget.h"
#include "ui_choosesetdatetimewidget.h"

ChooseSetDateTimeWidget::ChooseSetDateTimeWidget(QWidget *parent)
:	QWidget(parent), ui(new Ui::ChooseSetDateTimeWidget)
{
	qDebug() << "ChooseSetDateTimeWidget::ChooseSetDateTimeWidget";
    ui->setupUi(this);
	d_choosed =ChooseSetNone;
}

ChooseSetDateTimeWidget::~ChooseSetDateTimeWidget()
{
	qDebug() << "ChooseSetDateTimeWidget::~ChooseSetDateTimeWidget";
    delete ui;
}

void ChooseSetDateTimeWidget::changeEvent(QEvent *e)
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

void ChooseSetDateTimeWidget::on_previousMenuButton_pressed()
{
	qDebug() << "ChooseSetDateTimeWidget::on_previousButton_pressed";
	emit returned();
}

void ChooseSetDateTimeWidget::on_setDateButton_pressed()
{
	qDebug() << "ChooseSetDateTimeWidget::on_setDateButton_pressed";
	d_choosed = ChooseSetDate;
	emit choosed(d_choosed);
	emit choosedSetDate();
}

void ChooseSetDateTimeWidget::on_setTimeButton_pressed()
{
	qDebug() << "ChooseSetDateTimeWidget::on_setTimeButton_pressed";
	d_choosed = ChooseSetTime;
	emit choosed(d_choosed);
	emit choosedSetTime();
}



