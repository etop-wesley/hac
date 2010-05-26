//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "heatingsettings.h"
#include "ui_heatingsettings.h"

HeatingSettings::HeatingSettings(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::HeatingSettings)
{
	qDebug() << "HeatingSettings::HeatingSettings";
    ui->setupUi(this);
}

HeatingSettings::~HeatingSettings()
{
	qDebug() << "HeatingSettings::~HeatingSettings";
    delete ui;
}

void HeatingSettings::changeEvent(QEvent *e)
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

void HeatingSettings::on_okButton_clicked()
{
	qDebug() << "HeatingSettings::on_okButton_clicked";
	close();
}

void HeatingSettings::on_cancelButton_clicked()
{
	qDebug() << "HeatingSettings::on_cancelButton_clicked";
	close();
}

void HeatingSettings::on_unitComboBox_currentIndexChanged(int index)
{
	qDebug() << "HeatingSettings::on_unitComboBox_currentIndexChanged" << index;
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

void HeatingSettings::on_minComboBox_currentIndexChanged(int index)
{
	qDebug() << "HeatingSettings::on_minComboBox_currentIndexChanged" << index;
	if (index > ui->maxComboBox->currentIndex()) {
		ui->maxComboBox->setCurrentIndex(index);
	}
}

void HeatingSettings::on_maxComboBox_currentIndexChanged(int index)
{
	qDebug() << "HeatingSettings::on_maxComboBox_currentIndexChanged" << index;
	if (index < ui->minComboBox->currentIndex()) {
		ui->minComboBox->setCurrentIndex(index);
	}
}



