//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "mainswitchpage.h"
#include "ui_mainswitchpage.h"
#include "gui.h"
#include "hacapplication.h"
#include <QSignalMapper>

MainSwitchPage::MainSwitchPage(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::MainSwitchPage)
{
	qDebug() << "MainSwitchPage::MainSwitchPage";
	
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

	connect(signalMapper, SIGNAL(mapped(int)),
			this, SLOT(on_button_clicked(int)));
}

MainSwitchPage::~MainSwitchPage()
{
	qDebug() << "MainSwitchPage::~MainSwitchPage";
    delete ui;
}

void MainSwitchPage::changeEvent(QEvent *e)
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

void MainSwitchPage::on_button_clicked(int index)
{
	qDebug() << "MainSwitchPage::on_button_clicked" << index;
	HacApp->showWindow("SwitchControlPage");
}


