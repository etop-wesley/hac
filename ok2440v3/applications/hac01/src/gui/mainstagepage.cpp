//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "mainstagepage.h"
#include "ui_mainstagepage.h"
#include "gui.h"
#include "mainstagemodepage.h"
#include "simulatehomesettings.h"
#include "airconditioningcontrolpage.h"
#include "heatingcontrolpage.h"
#include "curtainscontrolpage.h"
#include "stagesettingspage.h"

MainStagePage::MainStagePage(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::MainStagePage)
{
	qDebug() << "MainStagePage::MainStagePage";
	
    ui->setupUi(this);
	setObjectName("MainStagePage");

	readSettings();
}

MainStagePage::~MainStagePage()
{
	qDebug() << "MainStagePage::~MainStagePage";

	writeSettings();
    delete ui;
}

void MainStagePage::changeEvent(QEvent *e)
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

void MainStagePage::on_listWidget_itemClicked(QListWidgetItem *item)
{
	qDebug() << "MainStagePage::on_listWidget_itemClicked";
	if (item == NULL)
		return;

	qDebug() << ui->listWidget->row(item);
	QWidget *widget = NULL;
	switch (ui->listWidget->row(item)) {
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
		widget = new StageSettingsPage; break;
		break;
	case 5: widget = new MainStageModePage; break;
	default: break;
	}
	if (widget != NULL) {
		widget->setGeometry(WINDOW_X, WINDOW_Y, WINDOW_W, WINDOW_H);
		widget->setAttribute(Qt::WA_DeleteOnClose);
		widget->show();
	}
}

void MainStagePage::readSettings()
{
	qDebug() << "MainStagePage::readSettings";
}

void MainStagePage::writeSettings()
{
	qDebug() << "MainStagePage::writeSettings";
}

