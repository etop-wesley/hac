//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "mainhomepage.h"
#include "ui_mainhomepage.h"
#include "gui.h"
#include "hacapplication.h"

MainHomePage::MainHomePage(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::MainHomePage)
{
	qDebug() << "MainHomePage::MainHomePage";
	
    ui->setupUi(this);
	setObjectName("MainHomePage");

	readSettings();
}

MainHomePage::~MainHomePage()
{
	qDebug() << "MainHomePage::~MainHomePage";

	writeSettings();
    delete ui;
}

void MainHomePage::changeEvent(QEvent *e)
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

void MainHomePage::on_listWidget_itemClicked(QListWidgetItem *item)
{
	qDebug() << "MainHomePage::on_listWidget_itemClicked";
	if (item == NULL)
		return;

	switch (ui->listWidget->row(item)) {
	case 1: HacApp->showWindow("AirConditioningControlPage"); break;
	case 2: HacApp->showWindow("HeatingControlPage"); break;
	case 3: HacApp->showWindow("CurtainsControlPage"); break;
	case 4: HacApp->showWindow("MainLightingPage"); break;
	case 5: HacApp->showWindow("MainSwitchPage"); break;
	case 6: HacApp->showWindow("MainStagePage"); break;
	case 7: HacApp->showWindow("SystemMain"); break;
	default: break;
	}
}

void MainHomePage::readSettings()
{
	qDebug() << "MainHomePage::readSettings";
}

void MainHomePage::writeSettings()
{
	qDebug() << "MainHomePage::writeSettings";
}

