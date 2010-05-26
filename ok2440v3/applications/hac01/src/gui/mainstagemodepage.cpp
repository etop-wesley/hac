//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "mainstagemodepage.h"
#include "ui_mainstagemodepage.h"
#include "gui.h"

MainStageModePage::MainStageModePage(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::MainStageModePage)
{
	qDebug() << "MainStageModePage::MainStageModePage";
	
    ui->setupUi(this);
	setObjectName("MainStageModePage");

	readSettings();
}

MainStageModePage::~MainStageModePage()
{
	qDebug() << "MainStageModePage::~MainStageModePage";

	writeSettings();
    delete ui;
}

void MainStageModePage::changeEvent(QEvent *e)
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

void MainStageModePage::on_listWidget_itemClicked(QListWidgetItem *item)
{
	qDebug() << "MainStageModePage::on_listWidget_itemClicked";
	if (item == NULL)
		return;

	qDebug() << ui->listWidget->row(item);
	QWidget *widget = NULL;
	switch (ui->listWidget->row(item)) {
	case 0: break;
	case 2: break;
	case 4: break;
	case 6: break;
	case 8: break;
	default: break;
	}
	if (widget != NULL) {
		widget->setGeometry(WINDOW_X, WINDOW_Y, WINDOW_W, WINDOW_H);
		widget->setAttribute(Qt::WA_DeleteOnClose);
		widget->show();
	}
}

void MainStageModePage::readSettings()
{
	qDebug() << "MainStageModePage::readSettings";
}

void MainStageModePage::writeSettings()
{
	qDebug() << "MainStageModePage::writeSettings";
}

