//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "lightcontrolpage.h"
#include "ui_lightcontrolpage.h"

LightControlPage::LightControlPage(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::LightControlPage)
{
	qDebug() << "LightControlPage::LightControlPage";
    ui->setupUi(this);

	on_lightOffButton_pressed();
}

LightControlPage::~LightControlPage()
{
	qDebug() << "LightControlPage::~LightControlPage";
    delete ui;
}

void LightControlPage::changeEvent(QEvent *e)
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

void LightControlPage::setBeUsedInStage()
{
	ui->titleLabel->hide();
}

void  LightControlPage::setNum(int num)
{
	ui->lcdNumber->display("0"+QString::number(num));
}

void LightControlPage::on_numUpButton_pressed()
{
	int num = ui->lcdNumber->value() + 1;
	if (num > 6)
		num = 1;
	ui->lcdNumber->display("0"+QString::number(num));
}

void LightControlPage::on_numDownButton_pressed()
{
	int num = ui->lcdNumber->value() - 1;
	if (num < 1)
		num = 6;
	ui->lcdNumber->display("0"+QString::number(num));
}

void LightControlPage::on_lightUpButton_pressed()
{
	ui->lightProgressBar->setValue(ui->lightProgressBar->value() + 5);
}

void LightControlPage::on_lightDownButton_pressed()
{
	ui->lightProgressBar->setValue(ui->lightProgressBar->value() - 5);
}

void LightControlPage::on_lightOnButton_pressed()
{
	ui->lightPixmapLabel->setPixmap(QPixmap(":/Hac/light-on.png"));
}

void LightControlPage::on_lightOffButton_pressed()
{
	ui->lightPixmapLabel->setPixmap(QPixmap(":/Hac/light-off.png"));
}

