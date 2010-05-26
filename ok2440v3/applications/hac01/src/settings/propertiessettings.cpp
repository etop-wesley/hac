//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "propertiessettings.h"
#include "ui_propertiessettings.h"
#include "gui.h"

static int min1 = 20;
static int max1 = 35;
static int min2 = 22;
static int max2 = 30;

PropertiesSettings::PropertiesSettings(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::PropertiesSettings)
{
	qDebug() << "PropertiesSettings::PropertiesSettings";
    ui->setupUi(this);

	ui->minLineEdit1->setText(QString::number(min1));
	ui->maxLineEdit1->setText(QString::number(max1));
	ui->minLineEdit2->setText(QString::number(min2));
	ui->maxLineEdit2->setText(QString::number(max2));
}

PropertiesSettings::~PropertiesSettings()
{
	qDebug() << "PropertiesSettings::~PropertiesSettings";
    delete ui;
}

void PropertiesSettings::changeEvent(QEvent *e)
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



void PropertiesSettings::on_upButton1_pressed()
{
	if (focusWidget() == ui->minLineEdit1) {
		if (min1++ > 100) min1 = 0;
		ui->minLineEdit1->setText(QString::number(min1));
	} else if (focusWidget() == ui->maxLineEdit1) {
		if (max1++ > 100) max1 = 0;
		ui->maxLineEdit1->setText(QString::number(max1));
	}
}

void PropertiesSettings::on_downButton1_pressed()
{
	if (focusWidget() == ui->minLineEdit1) {
		if (min1-- < 0) min1 = 100;
		ui->minLineEdit1->setText(QString::number(min1));
	} else if (focusWidget() == ui->maxLineEdit1) {
		if (max1-- < 0) max1 = 100;
		ui->maxLineEdit1->setText(QString::number(max1));
	}
}

void PropertiesSettings::on_upButton2_pressed()
{
	if (focusWidget() == ui->minLineEdit2) {
		if (min2++ > 100) min2 = 0;
		ui->minLineEdit2->setText(QString::number(min2));
	} else if (focusWidget() == ui->maxLineEdit2) {
		if (max2++ > 100) max2 = 0;
		ui->maxLineEdit2->setText(QString::number(max2));
	}

}

void PropertiesSettings::on_downButton2_pressed()
{
	if (focusWidget() == ui->minLineEdit2) {
		if (min2-- < 0) min2 = 100;
		ui->minLineEdit2->setText(QString::number(min2));
	} else if (focusWidget() == ui->maxLineEdit2) {
		if (max2-- < 0) max2 = 100;
		ui->maxLineEdit2->setText(QString::number(max2));
	}

}


void PropertiesSettings::on_okButton_pressed()
{
	close();
}

void PropertiesSettings::on_cancelButton_pressed()
{
	close();
}

