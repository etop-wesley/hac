//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "mainfanpage.h"
#include "ui_mainfanpage.h"
#include "fanscheduleset.h"

MainFanPage::MainFanPage(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::MainFanPage)
{
	qDebug() << "MainFanPage::MainFanPage";
    ui->setupUi(this);

}

MainFanPage::~MainFanPage()
{
	qDebug() << "MainFanPage::~MainFanPage";
    delete ui;
}

void MainFanPage::changeEvent(QEvent *e)
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

void MainFanPage::on_startButton_clicked()
{
	qDebug() << "MainFanPage::on_startButton_clicked";

}

void MainFanPage::on_stopButton_clicked()
{
	qDebug() << "MainFanPage::on_stopButton_clicked";

}

void MainFanPage::on_scheduleButton_clicked()
{
	qDebug() << "MainFanPage::on_scheduleButton_clicked";

	FanScheduleSet *w = new FanScheduleSet();
	w->setAttribute(Qt::WA_DeleteOnClose, true);

	w->showMaximized();
}

