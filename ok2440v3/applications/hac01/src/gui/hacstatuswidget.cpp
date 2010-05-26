//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "hacstatuswidget.h"
#include "ui_hacstatuswidget.h"
#include "gui.h"
#include "hacapplication.h"

HacStatusWidget::HacStatusWidget(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::HacStatusWidget)
{
	qDebug() << "HacStatusWidget::HacStatusWidget";
    ui->setupUi(this);
	setObjectName("HacStatusWidget");

	connect(ui->homeButton, SIGNAL(clicked()), this, SIGNAL(homeClicked()));
	connect(ui->backButton, SIGNAL(clicked()), this, SIGNAL(backClicked()));
	connect(ui->clockLabel, SIGNAL(clicked()), this, SIGNAL(clockClicked()));
}

HacStatusWidget::~HacStatusWidget()
{
	qDebug() << "HacStatusWidget::~HacStatusWidget";
    delete ui;
}

void HacStatusWidget::changeEvent(QEvent *e)
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

void HacStatusWidget::on_homeButton_clicked()
{
	qDebug() << "HacMainWindow::on_homeButton_clicked";
    foreach (QWidget *widget, QApplication::topLevelWidgets())
    {
		if (widget->objectName() != "HacStatusWidget"
			&& widget->objectName() != "MainHomePage") {
			widget->close();
		}
    }

}

void HacStatusWidget::on_backButton_clicked()
{
	qDebug() << "HacMainWindow::on_backButton_clicked";
	QWidget *widget = QApplication::topLevelAt(160, 120);
	if (widget->objectName() != "HacStatusWidget"
		&& widget->objectName() != "MainHomePage") {
		widget->close();
	}
}

void HacStatusWidget::on_clockLabel_clicked()
{
	qDebug() << "HacMainWindow::on_clockLabel_clicked";
	HacApp->showWindow("DateTimeSettings");
}

