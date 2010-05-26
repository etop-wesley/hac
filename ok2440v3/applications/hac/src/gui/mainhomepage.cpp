//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "mainhomepage.h"
#include "ui_mainhomepage.h"

MainHomePage::MainHomePage(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::MainHomePage)
{
	qDebug() << "MainHomePage::MainHomePage";
	
    ui->setupUi(this);

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

void MainHomePage::readSettings()
{
	qDebug() << "MainHomePage::readSettings";
}

void MainHomePage::writeSettings()
{
	qDebug() << "MainHomePage::writeSettings";
}

