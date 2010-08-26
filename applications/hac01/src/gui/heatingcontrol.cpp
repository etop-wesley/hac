//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QSignalMapper>
#include "heatingcontrol.h"
#include "ui_heatingcontrol.h"

HeatingControl::HeatingControl(QWidget *parent, Qt::WindowFlags f)
:	QWidget(parent, f), ui(new Ui::HeatingControl)
{
	qDebug() << "HeatingControl::HeatingControl";
    ui->setupUi(this);

	QPixmap normalPixmap;
	QPixmap activePixmap;
	QPalette pal;

	normalPixmap.load(":/hac01/images/button-background-normal-64x64.png");
	activePixmap.load(":/hac01/images/button-background-active-64x64.png");

    pal = ui->tempUpButton->palette();
    pal.setBrush(QPalette::Button, normalPixmap);
    pal.setBrush(QPalette::Light, activePixmap);
    ui->tempUpButton->setPalette(pal);
	ui->tempUpButton->setPaletteBrushPanel(true);

    pal = ui->tempDownButton->palette();
    pal.setBrush(QPalette::Button, normalPixmap);
    pal.setBrush(QPalette::Light, activePixmap);
    ui->tempDownButton->setPalette(pal);
	ui->tempDownButton->setPaletteBrushPanel(true);

	normalPixmap.load(":/hac01/images/button-background-normal-128x64.png");
	activePixmap.load(":/hac01/images/button-background-active-128x64.png");

    pal = ui->startButton->palette();
    pal.setBrush(QPalette::Button, normalPixmap);
    pal.setBrush(QPalette::Light, activePixmap);
    ui->startButton->setPalette(pal);
	ui->startButton->setPaletteBrushPanel(true);

    pal = ui->stopButton->palette();
    pal.setBrush(QPalette::Button, normalPixmap);
    pal.setBrush(QPalette::Light, activePixmap);
    ui->stopButton->setPalette(pal);
	ui->stopButton->setPaletteBrushPanel(true);

/*
    QIcon icon;
    icon.addFile(":/HAC01/button-background-normal-64x64.png", QSize(), QIcon::Normal);
    icon.addFile(":/HAC01/button-background-active-64x64.png", QSize(), QIcon::Active);
    if (!icon.isNull()) {
        ui->tempUpButton->setAutoFillBackground(false);
        ui->tempUpButton->setBackgroundIcon(icon);

        ui->tempDownButton->setAutoFillBackground(false);
        ui->tempDownButton->setBackgroundIcon(icon);
    } else {
        qDebug() << "Can not found button-background-64x64.png";
    }

    icon.addFile(":/HAC01/button-background-normal-128x64.png", QSize(), QIcon::Normal);
    icon.addFile(":/HAC01/button-background-active-128x64.png", QSize(), QIcon::Active);
    if (!icon.isNull()) {
        ui->startButton->setAutoFillBackground(false);
        ui->startButton->setBackgroundIcon(icon);

        ui->stopButton->setAutoFillBackground(false);
        ui->stopButton->setBackgroundIcon(icon);
    } else {
        qDebug() << "Can not found button-background-128x64.png";
    }
*/
    QSignalMapper *buttonsSignalMapper = new QSignalMapper(this);
    connect(ui->tempUpButton, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->tempUpButton, ui->tempUpButton->objectName());
    connect(ui->tempDownButton, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->tempDownButton, ui->tempDownButton->objectName());

    connect(ui->startButton, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->startButton, ui->startButton->objectName());
    connect(ui->stopButton, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->stopButton, ui->stopButton->objectName());

    connect(buttonsSignalMapper, SIGNAL(mapped(const QString &)),
            this, SLOT(OnButtonClicked(const QString &)));

}

HeatingControl::~HeatingControl()
{
	qDebug() << "HeatingControl::~HeatingControl";
    delete ui;
}

void HeatingControl::changeEvent(QEvent *e)
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

static int temp = 27;

void HeatingControl::OnButtonClicked(const QString &name)
{
	qDebug() << "AcControl::OnButtonClicked" << name;
    if (name == "tempUpButton" || name == "tempDownButton") {
        temp += (name == "tempUpButton" ? 1 : -1);
        if (temp > 30) temp = 30;
        if (temp < 16) temp = 16;
        ui->setTempLabel->setText(QString::number(temp));
    } else if (name == "startButton" || name == "stopButton") {
        if (name == "startButton")
            ui->stopButton->setChecked(false);
        else if (name == "stopButton")
            ui->startButton->setChecked(false);
    }
}



