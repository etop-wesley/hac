//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "mainairconditioningpage.h"
#include "ui_mainairconditioningpage.h"
#include "gui.h"
#include "airconditioningcontrolpage.h"
#include <QSignalMapper>

MainAirConditioningPage::MainAirConditioningPage(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::MainAirConditioningPage)
{
	qDebug() << "MainAirConditioningPage::MainAirConditioningPage";
	
    ui->setupUi(this);

	QSignalMapper *signalMapper = new QSignalMapper(this);
	QPushButton *button;
	button = ui->pushButton_1;
	connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
	signalMapper->setMapping(button, 1);
	button = ui->pushButton_2;
	connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
	signalMapper->setMapping(button, 2);
	button = ui->pushButton_3;
	connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
	signalMapper->setMapping(button, 3);
	button = ui->pushButton_4;
	connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
	signalMapper->setMapping(button, 4);
	button = ui->pushButton_5;
	connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
	signalMapper->setMapping(button, 5);
	button = ui->pushButton_6;
	connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
	signalMapper->setMapping(button, 6);
	button = ui->pushButton_7;
	connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
	signalMapper->setMapping(button, 7);
	button = ui->pushButton_8;
	connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
	signalMapper->setMapping(button, 8);
	button = ui->pushButton_9;
	connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
	signalMapper->setMapping(button, 9);
	button = ui->pushButton_10;
	connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
	signalMapper->setMapping(button, 10);

	connect(signalMapper, SIGNAL(mapped(int)),
			this, SLOT(on_button_clicked(int)));

}

MainAirConditioningPage::~MainAirConditioningPage()
{
	qDebug() << "MainAirConditioningPage::~MainAirConditioningPage";
    delete ui;
}

void MainAirConditioningPage::changeEvent(QEvent *e)
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

void MainAirConditioningPage::on_button_clicked(int index)
{
	qDebug() << "MainAirConditioningPage::on_button_clicked" << index;
	AirConditioningControlPage *page = new AirConditioningControlPage;
	page->setGeometry(WINDOW_X, WINDOW_Y, WINDOW_W, WINDOW_H);
	page->setAttribute(Qt::WA_DeleteOnClose);
	page->show();

}

