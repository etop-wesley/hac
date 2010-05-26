//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "enterpasswordwidget.h"
#include "ui_enterpasswordwidget.h"

EnterPasswordWidget::EnterPasswordWidget(QWidget *parent)
:	QWidget(parent), ui(new Ui::EnterPasswordWidget)
{
	qDebug() << "EnterPasswordWidget::EnterPasswordWidget";
    ui->setupUi(this);
}

EnterPasswordWidget::~EnterPasswordWidget()
{
	qDebug() << "EnterPasswordWidget::~EnterPasswordWidget";
    delete ui;
}

void EnterPasswordWidget::changeEvent(QEvent *e)
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

void EnterPasswordWidget::on_cancelButton_pressed()
{
	qDebug() << "EnterPasswordWidget::on_cancelButton_pressed";
	emit cancelled();
}

void EnterPasswordWidget::on_doneButton_pressed()
{
	qDebug() << "EnterPasswordWidget::on_doneButton_pressed";
	emit done();
}

void EnterPasswordWidget::on_helpButton_pressed()
{
	qDebug() << "EnterPasswordWidget::on_helpButton_pressed";
	emit help();
}



