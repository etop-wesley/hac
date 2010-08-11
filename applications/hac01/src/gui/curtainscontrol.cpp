//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "curtainscontrol.h"
#include "ui_curtainscontrol.h"

CurtainsControl::CurtainsControl(QWidget *parent, Qt::WindowFlags f)
:	QWidget(parent, f), ui(new Ui::CurtainsControl)
{
	qDebug() << "CurtainsControl::CurtainsControl";
    ui->setupUi(this);
}

CurtainsControl::~CurtainsControl()
{
	qDebug() << "CurtainsControl::~CurtainsControl";
    delete ui;
}

void CurtainsControl::changeEvent(QEvent *e)
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


