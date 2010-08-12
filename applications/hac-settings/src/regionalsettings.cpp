//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "regionalsettings.h"
#include "ui_regionalsettings.h"
#include "gui.h"

RegionalSettings::RegionalSettings(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::RegionalSettings)
{
	qDebug() << "RegionalSettings::RegionalSettings";
    ui->setupUi(this);

	ui->okButton->setBackgroundImage(":/Hac/background-rect-button.png", true);
	ui->cancelButton->setBackgroundImage(":/Hac/background-rect-button.png", true);
}

RegionalSettings::~RegionalSettings()
{
	qDebug() << "RegionalSettings::~RegionalSettings";
    delete ui;
}

void RegionalSettings::changeEvent(QEvent *e)
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

void RegionalSettings::on_okButton_pressed()
{
	close();
}

void RegionalSettings::on_cancelButton_pressed()
{
	close();
}

