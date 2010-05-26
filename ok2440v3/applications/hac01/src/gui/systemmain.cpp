//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "systemmain.h"
#include "ui_systemmain.h"
#include "gui.h"
#include "hacapplication.h"


SystemMain::SystemMain(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::SystemMain)
{
	qDebug() << "SystemMain::SystemMain";
	
    ui->setupUi(this);
	setObjectName("SystemMain");
}

SystemMain::~SystemMain()
{
	qDebug() << "SystemMain::~SystemMain";
    delete ui;
}

void SystemMain::changeEvent(QEvent *e)
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

void SystemMain::on_listWidget_itemClicked(QListWidgetItem *item)
{
	qDebug() << "SystemMain::on_listWidget_itemClicked";
	if (item == NULL)
		return;

	QWidget *widget = NULL;
	switch (ui->listWidget->row(item)) {
	case 0: HacApp->showWindow("RegionalSettings"); break;
	case 1: HacApp->showWindow("DateTimeSettings"); break;
	case 2: HacApp->showWindow("PropertiesSettings"); break;
	case 3:
	case 4:
	case 5:
	default: break;
	}
}

