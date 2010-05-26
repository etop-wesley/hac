//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "settimewidget.h"
#include "ui_settimewidget.h"

SetTimeWidget::SetTimeWidget(QWidget *parent)
:	QWidget(parent), ui(new Ui::SetTimeWidget)
{
	qDebug() << "SetTimeWidget::SetTimeWidget";
    ui->setupUi(this);
}

SetTimeWidget::~SetTimeWidget()
{
	qDebug() << "SetTimeWidget::~SetTimeWidget";
    delete ui;
}

void SetTimeWidget::changeEvent(QEvent *e)
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

void SetTimeWidget::on_cancelButton_pressed()
{
	qDebug() << "SetTimeWidget::on_cancelButton_pressed";
	emit cancelled();
}

void SetTimeWidget::on_doneButton_pressed()
{
	qDebug() << "SetTimeWidget::on_doneButton_pressed";
	emit done();
}




