//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "mainheatingpage.h"
#include "ui_mainheatingpage.h"
#include "gui.h"
#include "hacapplication.h"

#include <QSignalMapper>

MainHeatingPage::MainHeatingPage(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::MainHeatingPage)
{
	qDebug() << "MainHeatingPage::MainHeatingPage";
	
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
	button = ui->pushButton_11;
	connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
	signalMapper->setMapping(button, 11);

	connect(signalMapper, SIGNAL(mapped(int)),
			this, SLOT(on_button_clicked(int)));

}

MainHeatingPage::~MainHeatingPage()
{
	qDebug() << "MainHeatingPage::~MainHeatingPage";
    delete ui;
}

void MainHeatingPage::changeEvent(QEvent *e)
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


void MainHeatingPage::on_button_clicked(int index)
{
	qDebug() << "MainHeatingPage::on_button_clicked" << index;
	HacApp->showWindow("HeatingControlPage");
}
