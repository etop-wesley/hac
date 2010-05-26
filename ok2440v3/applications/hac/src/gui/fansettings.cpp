//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "fansettings.h"
#include "ui_fansettings.h"
#include "hachelp.h"

FanSettings::FanSettings(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::FanSettings)
{
	qDebug() << "FanSettings::FanSettings";
    ui->setupUi(this);
	ui->unitComboBox->setCurrentIndex(0);
}

FanSettings::~FanSettings()
{
	qDebug() << "FanSettings::~FanSettings";
    delete ui;
}

void FanSettings::changeEvent(QEvent *e)
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

void FanSettings::on_okButton_clicked()
{
	qDebug() << "FanSettings::on_okButton_clicked";
	close();
}

void FanSettings::on_cancelButton_clicked()
{
	qDebug() << "FanSettings::on_cancelButton_clicked";
	close();
}

void FanSettings::on_unitComboBox_currentIndexChanged(int index)
{
	qDebug() << "FanSettings::on_unitComboBox_currentIndexChanged" << index;
	if (index == 0 || index == 1) {
		ui->minComboBox->clear();
		ui->maxComboBox->clear();
		QStringList tempStrings;
		//QString unitString = index == 0 ? "C" : "F"; // FIXME
		for (int i = 1; i <= 100; i++)
			tempStrings << QString::number(i);
		ui->minComboBox->addItems(tempStrings);
		ui->maxComboBox->addItems(tempStrings);
	}
}

void FanSettings::on_minComboBox_currentIndexChanged(int index)
{
	qDebug() << "FanSettings::on_minComboBox_currentIndexChanged" << index;
	if (index > ui->maxComboBox->currentIndex()) {
		ui->maxComboBox->setCurrentIndex(index);
	}
}

void FanSettings::on_maxComboBox_currentIndexChanged(int index)
{
	qDebug() << "FanSettings::on_maxComboBox_currentIndexChanged" << index;
	if (index < ui->minComboBox->currentIndex()) {
		ui->minComboBox->setCurrentIndex(index);
	}

}



