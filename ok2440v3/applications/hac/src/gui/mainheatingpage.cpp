//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "mainheatingpage.h"
#include "ui_mainheatingpage.h"

MainHeatingPage::MainHeatingPage(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::MainHeatingPage)
{
	qDebug() << "MainHeatingPage::MainHeatingPage";
	
    ui->setupUi(this);
	readSettings();
}

MainHeatingPage::~MainHeatingPage()
{
	qDebug() << "MainHeatingPage::~MainHeatingPage";

	writeSettings();
    delete ui;
}

void MainHeatingPage::changeEvent(QEvent *e)
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

void MainHeatingPage::on_startButton_clicked()
{
	qDebug() << "MainHeatingPage::on_startButton_clicked";

}

void MainHeatingPage::on_stopButton_clicked()
{
	qDebug() << "MainHeatingPage::on_stopButton_clicked";

}

void MainHeatingPage::on_scheduleButton_clicked()
{
	qDebug() << "MainHeatingPage::on_scheduleButton_clicked";

}



void MainHeatingPage::readSettings()
{
	qDebug() << "MainHeatingPage::readSettings";
}

void MainHeatingPage::writeSettings()
{
	qDebug() << "MainHeatingPage::writeSettings";
}

