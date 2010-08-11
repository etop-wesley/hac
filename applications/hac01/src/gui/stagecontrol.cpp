//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "stagecontrol.h"
#include "ui_stagecontrol.h"

StageControl::StageControl(QWidget *parent, Qt::WindowFlags f)
:	QWidget(parent, f), ui(new Ui::StageControl)
{
	qDebug() << "StageControl::StageControl";
    ui->setupUi(this);
}

StageControl::~StageControl()
{
	qDebug() << "StageControl::~StageControl";
    delete ui;
}

void StageControl::changeEvent(QEvent *e)
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


