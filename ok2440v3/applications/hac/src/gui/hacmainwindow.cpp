//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "hacmainwindow.h"
#include "ui_hacmainwindow.h"

HacMainWindow::HacMainWindow(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::HacMainWindow)
{
	qDebug() << "HacMainWindow::HacMainWindow";
	
    ui->setupUi(this);

	//setStyleSheet(Help::ReadStyleSheetFromFile(":/Hac-StyleSheets/HacMainWindow"));

	readSettings();
}

HacMainWindow::~HacMainWindow()
{
	qDebug() << "HacMainWindow::~HacMainWindow";

	writeSettings();
    delete ui;
}

void HacMainWindow::changeEvent(QEvent *e)
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

void HacMainWindow::readSettings()
{
	qDebug() << "HacMainWindow::readSettings";
}

void HacMainWindow::writeSettings()
{
	qDebug() << "HacMainWindow::writeSettings";
}


