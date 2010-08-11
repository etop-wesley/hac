//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QSignalMapper>
#include "accontrol.h"
#include "ui_accontrol.h"

AcControl::AcControl(QWidget *parent, Qt::WindowFlags f)
:	QWidget(parent, f), ui(new Ui::AcControl)
{
	qDebug() << "AcControl::AcControl";
    ui->setupUi(this);
/*
    QIcon icon;
    icon.addFile(":/HAC01/button-background-normal-64x64.png", QSize(), QIcon::Normal);
    icon.addFile(":/HAC01/button-background-active-64x64.png", QSize(), QIcon::Active);
    if (!icon.isNull()) {
        ui->tempUpButton->setAutoFillBackground(false);
        ui->tempUpButton->setBackgroundIcon(icon);

        ui->tempDownButton->setAutoFillBackground(false);
        ui->tempDownButton->setBackgroundIcon(icon);

        ui->modeUpButton->setAutoFillBackground(false);
        ui->modeUpButton->setBackgroundIcon(icon);

        ui->modeDownButton->setAutoFillBackground(false);
        ui->modeDownButton->setBackgroundIcon(icon);

        ui->speedLowButton->setAutoFillBackground(false);
        ui->speedLowButton->setBackgroundIcon(icon);

        ui->speedMidButton->setAutoFillBackground(false);
        ui->speedMidButton->setBackgroundIcon(icon);

        ui->speedHighButton->setAutoFillBackground(false);
        ui->speedHighButton->setBackgroundIcon(icon);
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

    connect(ui->modeUpButton, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->modeUpButton, ui->modeUpButton->objectName());
    connect(ui->modeDownButton, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->modeDownButton, ui->modeDownButton->objectName());

    connect(ui->speedLowButton, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->speedLowButton, ui->speedLowButton->objectName());
    connect(ui->speedMidButton, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->speedMidButton, ui->speedMidButton->objectName());
    connect(ui->speedHighButton, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->speedHighButton, ui->speedHighButton->objectName());

    connect(ui->startButton, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->startButton, ui->startButton->objectName());
    connect(ui->stopButton, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->stopButton, ui->stopButton->objectName());

    connect(buttonsSignalMapper, SIGNAL(mapped(const QString &)),
            this, SLOT(OnButtonClicked(const QString &)));
}

AcControl::~AcControl()
{
	qDebug() << "AcControl::~AcControl";
    delete ui;
}

void AcControl::changeEvent(QEvent *e)
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
static int mode = 2;
static char * mode_texts[4] = { "Refrigerate", "Febricant", "Auto", "Blow"};

void AcControl::OnButtonClicked(const QString &name)
{
	qDebug() << "AcControl::OnButtonClicked" << name;
    if (name == "tempUpButton" || name == "tempDownButton") {
        temp += (name == "tempUpButton" ? 1 : -1);
        if (temp > 30) temp = 30;
        if (temp < 16) temp = 16;
        ui->setTempLabel->setText(QString::number(temp));
    } else if (name == "modeUpButton" || name == "modeDownButton") {
        mode += (name == "modeUpButton" ? 1 : -1);
        if (mode > 3) mode = 0;
        if (mode < 0) mode = 3;
        ui->modeLabel->setText(QString(mode_texts[mode]));
    } else if (name == "speedLowButton" || name == "speedMidButton" || name == "speedHighButton") {
        if (name == "speedLowButton") {
            ui->speedMidButton->setChecked(false);
            ui->speedHighButton->setChecked(false);
        } else if (name == "speedMidButton") {
            ui->speedLowButton->setChecked(false);
            ui->speedHighButton->setChecked(false);
        } else if (name == "speedHighButton") {
            ui->speedLowButton->setChecked(false);
            ui->speedMidButton->setChecked(false);
        }
    } else if (name == "startButton" || name == "stopButton") {
        if (name == "startButton")
            ui->stopButton->setChecked(false);
        else if (name == "stopButton")
            ui->startButton->setChecked(false);
    }
}


