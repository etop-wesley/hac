//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QSignalMapper>
#include "switchescontrol.h"
#include "ui_switchescontrol.h"

SwitchesControl::SwitchesControl(QWidget *parent, Qt::WindowFlags f)
:	QWidget(parent, f), ui(new Ui::SwitchesControl)
{
	qDebug() << "SwitchesControl::SwitchesControl";
    ui->setupUi(this);
/*
    QIcon icon;
    icon.addFile(":/HAC01/button-background-normal-128x128.png", QSize(), QIcon::Normal);
    icon.addFile(":/HAC01/button-background-active-128x128.png", QSize(), QIcon::Active);
    if (!icon.isNull()) {
        ui->switch1Button->setAutoFillBackground(false);
        ui->switch1Button->setBackgroundIcon(icon);
        ui->switch2Button->setAutoFillBackground(false);
        ui->switch2Button->setBackgroundIcon(icon);
        ui->switch3Button->setAutoFillBackground(false);
        ui->switch3Button->setBackgroundIcon(icon);
    } else {
        qDebug() << "Can not found button-background-128x128.png";
    }
    //icon.addFile(":/HAC01/button-background-normal-64x128.png", QSize(), QIcon::Normal);
    //icon.addFile(":/HAC01/button-background-active-64x128.png", QSize(), QIcon::Active);
    if (!icon.isNull()) {
        ui->singleOnButton->setAutoFillBackground(false);
        ui->singleOnButton->setBackgroundIcon(icon);

        ui->singleOffButton->setAutoFillBackground(false);
        ui->singleOffButton->setBackgroundIcon(icon);
    } else {
        qDebug() << "Can not found button-background-64x128.png";
    }

    icon.addFile(":/HAC01/button-background-normal-64x64.png", QSize(), QIcon::Normal);
    icon.addFile(":/HAC01/button-background-active-64x64.png", QSize(), QIcon::Active);
    if (!icon.isNull()) {
        ui->allOnButton->setAutoFillBackground(false);
        ui->allOnButton->setBackgroundIcon(icon);

        ui->allOffButton->setAutoFillBackground(false);
        ui->allOffButton->setBackgroundIcon(icon);
    } else {
        qDebug() << "Can not found button-background-64x64.png";
    }
*/

    QSignalMapper *buttonsSignalMapper = new QSignalMapper(this);
    connect(ui->switch1Button, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->switch1Button, ui->switch1Button->objectName());
    connect(ui->switch2Button, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->switch2Button, ui->switch2Button->objectName());
    connect(ui->switch3Button, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->switch3Button, ui->switch3Button->objectName());

    connect(ui->singleOnButton, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->singleOnButton, ui->singleOnButton->objectName());
    connect(ui->singleOffButton, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->singleOffButton, ui->singleOffButton->objectName());

    connect(ui->allOnButton, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->allOnButton, ui->allOnButton->objectName());
    connect(ui->allOffButton, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->allOffButton, ui->allOffButton->objectName());

    connect(buttonsSignalMapper, SIGNAL(mapped(const QString &)),
            this, SLOT(OnButtonClicked(const QString &)));

}

SwitchesControl::~SwitchesControl()
{
	qDebug() << "SwitchesControl::~SwitchesControl";
    delete ui;
}

void SwitchesControl::changeEvent(QEvent *e)
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

void SwitchesControl::OnButtonClicked(const QString &name)
{
	qDebug() << "SwitchesControl::OnButtonClicked" << name;
    if (name == "singleOnButton" || name == "singleOffButton") {
        if (name == "singleOnButton")
            ui->singleOffButton->setChecked(false);
        else if (name == "singleOffButton")
            ui->singleOnButton->setChecked(false);
    } else if (name == "allOnButton" || name == "allOffButton") {
        if (name == "allOnButton")
            ui->allOffButton->setChecked(false);
        else if (name == "singleOffButton")
            ui->allOnButton->setChecked(false);
    } else if (name == "switch1Button" || name == "switch2Button" || name == "switch3Button") {
        if (name == "switch1Button") {
            ui->switch2Button->setChecked(false);
            ui->switch3Button->setChecked(false);
        } else if (name == "switch2Button") {
            ui->switch1Button->setChecked(false);
            ui->switch3Button->setChecked(false);
        } else if (name == "switch3Button") {
            ui->switch1Button->setChecked(false);
            ui->switch2Button->setChecked(false);
        }
    }
}


