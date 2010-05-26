//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "switchcontrolpage.h"
#include "ui_switchcontrolpage.h"

SwitchControlPage::SwitchControlPage(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::SwitchControlPage)
{
	qDebug() << "SwitchControlPage::SwitchControlPage";
    ui->setupUi(this);

	on_lightOffButton_pressed();

}

SwitchControlPage::~SwitchControlPage()
{
	qDebug() << "SwitchControlPage::~SwitchControlPage";
    delete ui;
}

void SwitchControlPage::changeEvent(QEvent *e)
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

void SwitchControlPage::setBeUsedInStage()
{
	ui->titleLabel->hide();
	ui->frame_2->hide();
	//ui->frame_3->hide();
}


void  SwitchControlPage::setNum(int num)
{
	ui->lcdNumber->display("0"+QString::number(num));
}

void SwitchControlPage::on_numUpButton_pressed()
{
	int num = ui->lcdNumber->value() + 1;
	if (num > 6)
		num = 1;
	ui->lcdNumber->display("0"+QString::number(num));
}

void SwitchControlPage::on_numDownButton_pressed()
{
	int num = ui->lcdNumber->value() - 1;
	if (num < 1)
		num = 6;
	ui->lcdNumber->display("0"+QString::number(num));
}

void SwitchControlPage::on_lightUpButton_pressed()
{
	//ui->lightProgressBar->setValue(ui->lightProgressBar->value() + 5);
}

void SwitchControlPage::on_lightDownButton_pressed()
{
	//ui->lightProgressBar->setValue(ui->lightProgressBar->value() - 5);
}

void SwitchControlPage::on_lightOnButton_pressed()
{
	ui->lightPixmapLabel->setPixmap(QPixmap(":/Hac/switch-on.png"));
}

void SwitchControlPage::on_lightOffButton_pressed()
{
	ui->lightPixmapLabel->setPixmap(QPixmap(":/Hac/switch-off.png"));
}

