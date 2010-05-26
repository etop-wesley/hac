//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "curtainscontrolpage.h"
#include "ui_curtainscontrolpage.h"

CurtainsControlPage::CurtainsControlPage(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::CurtainsControlPage)
{
	qDebug() << "CurtainsControlPage::CurtainsControlPage";
    ui->setupUi(this);
}

CurtainsControlPage::~CurtainsControlPage()
{
	qDebug() << "CurtainsControlPage::~CurtainsControlPage";
    delete ui;
}

void CurtainsControlPage::changeEvent(QEvent *e)
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

void CurtainsControlPage::setBeUsedInStage()
{
	ui->titleLabel->hide();
}

