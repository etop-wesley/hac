//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "setvocationdatewidget.h"
#include "ui_setvocationdatewidget.h"

SetVocationDateWidget::SetVocationDateWidget(QWidget *parent)
:	QWidget(parent), ui(new Ui::SetVocationDateWidget)
{
	qDebug() << "SetVocationDateWidget::SetVocationDateWidget";
    ui->setupUi(this);
}

SetVocationDateWidget::~SetVocationDateWidget()
{
	qDebug() << "SetVocationDateWidget::~SetVocationDateWidget";
    delete ui;
}

void SetVocationDateWidget::changeEvent(QEvent *e)
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

void SetVocationDateWidget::on_cancelButton_pressed()
{
	qDebug() << "SetVocationDateWidget::on_cancelButton_pressed";
	emit cancelled();
}

void SetVocationDateWidget::on_nextButton_pressed()
{
	qDebug() << "SetVocationDateWidget::on_nextButton_pressed";
	emit nexted();
}




