//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "mainlightingpage.h"
#include "ui_mainlightingpage.h"
#include "lightingscheduleset.h"
#include "lightingstageselect.h"

MainLightingPage::MainLightingPage(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::MainLightingPage)
{
	qDebug() << "MainLightingPage::MainLightingPage";
    ui->setupUi(this);
}

MainLightingPage::~MainLightingPage()
{
	qDebug() << "MainLightingPage::~MainLightingPage";
    delete ui;
}

void MainLightingPage::changeEvent(QEvent *e)
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

void MainLightingPage::on_startButton_clicked()
{
	qDebug() << "MainLightingPage::on_startButton_clicked";

}

void MainLightingPage::on_stopButton_clicked()
{
	qDebug() << "MainLightingPage::on_stopButton_clicked";

}

void MainLightingPage::on_scheduleButton_clicked()
{
	qDebug() << "MainLightingPage::on_scheduleButton_clicked";
	LightingScheduleSet *w = new LightingScheduleSet;
	w->setAttribute(Qt::WA_DeleteOnClose, true);

	w->showMaximized();

}

void MainLightingPage::on_stageButton_clicked()
{
	qDebug() << "MainLightingPage::on_stageButton_clicked";
	LightingStageSelect *w = new LightingStageSelect;
	w->setAttribute(Qt::WA_DeleteOnClose, true);

	w->showMaximized();

}

