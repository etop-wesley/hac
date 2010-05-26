//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "hacmainwindow.h"
#include "ui_hacmainwindow.h"
#include "gui.h"
#include "hacapplication.h"

HacMainWindow::HacMainWindow(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::HacMainWindow)
{
	qDebug() << "HacMainWindow::HacMainWindow";
	
    ui->setupUi(this);
	ui->statusWidget->setFixedHeight(TASKPANEL_H);

	connect(ui->statusWidget, SIGNAL(homeClicked()), this, SLOT(on_statusWidget_homeClicked()));
	connect(ui->statusWidget, SIGNAL(backClicked()), this, SLOT(on_statusWidget_backClicked()));
	connect(ui->statusWidget, SIGNAL(clockClicked()), this, SLOT(on_statusWidget_clockClicked()));

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

void HacMainWindow::resizeEvent(QResizeEvent *e)
{
	qDebug() << "HacMainWindow::resizeEvent";
	QWidget::resizeEvent(e);

}


void HacMainWindow::on_statusWidget_homeClicked()
{
	qDebug() << "HacMainWindow::on_statusWidget_homeClicked";
    foreach (QWidget *widget, QApplication::topLevelWidgets())
    {
		if (widget->objectName() != "HacMainWindow"
			&& widget->objectName() != "MainHomePage") {
			widget->close();
		}
    }

}

void HacMainWindow::on_statusWidget_backClicked()
{
	qDebug() << "HacMainWindow::on_statusWidget_backClicked";
	QWidget *widget = QApplication::topLevelAt(160, 120);
	if (widget->objectName() != "HacMainWindow"
		&& widget->objectName() != "MainHomePage") {
		widget->close();
	}
}

void HacMainWindow::on_statusWidget_clockClicked()
{
	qDebug() << "HacMainWindow::on_statusWidget_clockClicked";
	HacApp->showWindow("DateTimeSettings");
}


void HacMainWindow::readSettings()
{
	qDebug() << "HacMainWindow::readSettings";
}

void HacMainWindow::writeSettings()
{
	qDebug() << "HacMainWindow::writeSettings";
}


