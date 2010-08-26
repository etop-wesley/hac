//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QSignalMapper>
#include "lightingscontrol.h"
#include "ui_lightingscontrol.h"

LightingsControl::LightingsControl(QWidget *parent, Qt::WindowFlags f)
:   QWidget(parent, f), ui(new Ui::LightingsControl)
{
    qDebug() << "LightingsControl::LightingsControl";
    ui->setupUi(this);

	QPixmap normalPixmap;
	QPixmap activePixmap;
	QPalette pal;

	normalPixmap.load(":/hac01/images/button-background-normal-128x64.png");
	activePixmap.load(":/hac01/images/button-background-active-128x64.png");

    pal = ui->allOnButton->palette();
    pal.setBrush(QPalette::Button, normalPixmap);
    pal.setBrush(QPalette::Light, activePixmap);
    ui->allOnButton->setPalette(pal);
	ui->allOnButton->setPaletteBrushPanel(true);

    pal = ui->allOffButton->palette();
    pal.setBrush(QPalette::Button, normalPixmap);
    pal.setBrush(QPalette::Light, activePixmap);
    ui->allOffButton->setPalette(pal);
	ui->allOffButton->setPaletteBrushPanel(true);

	normalPixmap.load(":/hac01/images/button-background-normal-64x128.png");
	activePixmap.load(":/hac01/images/button-background-active-64x128.png");

    pal = ui->singleOnButton->palette();
    pal.setBrush(QPalette::Button, normalPixmap);
    pal.setBrush(QPalette::Light, activePixmap);
    ui->singleOnButton->setPalette(pal);
	ui->singleOnButton->setPaletteBrushPanel(true);

    pal = ui->singleOffButton->palette();
    pal.setBrush(QPalette::Button, normalPixmap);
    pal.setBrush(QPalette::Light, activePixmap);
    ui->singleOffButton->setPalette(pal);
	ui->singleOffButton->setPaletteBrushPanel(true);


	normalPixmap.load(":/hac01/images/button-background-normal-32x32.png");
	activePixmap.load(":/hac01/images/button-background-active-32x32.png");

    pal = ui->pushButton_1->palette();
    pal.setBrush(QPalette::Button, normalPixmap);
    pal.setBrush(QPalette::Light, activePixmap);
    ui->pushButton_1->setPalette(pal);
	ui->pushButton_1->setPaletteBrushPanel(true);

    pal = ui->pushButton_2->palette();
    pal.setBrush(QPalette::Button, normalPixmap);
    pal.setBrush(QPalette::Light, activePixmap);
    ui->pushButton_2->setPalette(pal);
	ui->pushButton_2->setPaletteBrushPanel(true);

    pal = ui->pushButton_3->palette();
    pal.setBrush(QPalette::Button, normalPixmap);
    pal.setBrush(QPalette::Light, activePixmap);
    ui->pushButton_3->setPalette(pal);
	ui->pushButton_3->setPaletteBrushPanel(true);

    pal = ui->pushButton_4->palette();
    pal.setBrush(QPalette::Button, normalPixmap);
    pal.setBrush(QPalette::Light, activePixmap);
    ui->pushButton_4->setPalette(pal);
	ui->pushButton_4->setPaletteBrushPanel(true);

    pal = ui->pushButton_5->palette();
    pal.setBrush(QPalette::Button, normalPixmap);
    pal.setBrush(QPalette::Light, activePixmap);
    ui->pushButton_5->setPalette(pal);
	ui->pushButton_5->setPaletteBrushPanel(true);

    pal = ui->pushButton_6->palette();
    pal.setBrush(QPalette::Button, normalPixmap);
    pal.setBrush(QPalette::Light, activePixmap);
    ui->pushButton_6->setPalette(pal);
	ui->pushButton_6->setPaletteBrushPanel(true);

    pal = ui->pushButton_7->palette();
    pal.setBrush(QPalette::Button, normalPixmap);
    pal.setBrush(QPalette::Light, activePixmap);
    ui->pushButton_7->setPalette(pal);
	ui->pushButton_7->setPaletteBrushPanel(true);

    pal = ui->pushButton_8->palette();
    pal.setBrush(QPalette::Button, normalPixmap);
    pal.setBrush(QPalette::Light, activePixmap);
    ui->pushButton_8->setPalette(pal);
	ui->pushButton_8->setPaletteBrushPanel(true);

    pal = ui->pushButton_9->palette();
    pal.setBrush(QPalette::Button, normalPixmap);
    pal.setBrush(QPalette::Light, activePixmap);
    ui->pushButton_9->setPalette(pal);
	ui->pushButton_9->setPaletteBrushPanel(true);

	pal = ui->pushButton_10->palette();
    pal.setBrush(QPalette::Button, normalPixmap);
    pal.setBrush(QPalette::Light, activePixmap);
    ui->pushButton_10->setPalette(pal);
	ui->pushButton_10->setPaletteBrushPanel(true);

    pal = ui->pushButton_11->palette();
    pal.setBrush(QPalette::Button, normalPixmap);
    pal.setBrush(QPalette::Light, activePixmap);
    ui->pushButton_11->setPalette(pal);
	ui->pushButton_11->setPaletteBrushPanel(true);

    pal = ui->pushButton_12->palette();
    pal.setBrush(QPalette::Button, normalPixmap);
    pal.setBrush(QPalette::Light, activePixmap);
    ui->pushButton_12->setPalette(pal);
	ui->pushButton_12->setPaletteBrushPanel(true);

/*
    QIcon icon;
    icon.addFile(":/HAC01/button-background-normal-128x64.png", QSize(), QIcon::Normal);
    icon.addFile(":/HAC01/button-background-active-128x64.png", QSize(), QIcon::Active);
    if (!icon.isNull()) {
        ui->allOnButton->setAutoFillBackground(false);
        ui->allOnButton->setBackgroundIcon(icon);
        ui->allOffButton->setAutoFillBackground(false);
        ui->allOffButton->setBackgroundIcon(icon);
    } else {
        qDebug() << "Can not found button-background-128x128.png";
    }

    icon.addFile(":/HAC01/button-background-normal-64x128.png", QSize(), QIcon::Normal);
    icon.addFile(":/HAC01/button-background-active-64x128.png", QSize(), QIcon::Active);
    if (!icon.isNull()) {
        ui->singleOnButton->setAutoFillBackground(false);
        ui->singleOnButton->setBackgroundIcon(icon);
        ui->singleOffButton->setAutoFillBackground(false);
        ui->singleOffButton->setBackgroundIcon(icon);
    } else {
        qDebug() << "Can not found button-background-64x128.png";
    }

    icon.addFile(":/HAC01/button-background-normal-32x32.png", QSize(), QIcon::Normal);
    icon.addFile(":/HAC01/button-background-active-32x32.png", QSize(), QIcon::Active);
    if (!icon.isNull()) {
        ui->pushButton_1->setAutoFillBackground(false);
        ui->pushButton_1->setBackgroundIcon(icon);
        ui->pushButton_2->setAutoFillBackground(false);
        ui->pushButton_2->setBackgroundIcon(icon);
        ui->pushButton_3->setAutoFillBackground(false);
        ui->pushButton_3->setBackgroundIcon(icon);
        ui->pushButton_4->setAutoFillBackground(false);
        ui->pushButton_4->setBackgroundIcon(icon);
        ui->pushButton_5->setAutoFillBackground(false);
        ui->pushButton_5->setBackgroundIcon(icon);
        ui->pushButton_6->setAutoFillBackground(false);
        ui->pushButton_6->setBackgroundIcon(icon);
        ui->pushButton_7->setAutoFillBackground(false);
        ui->pushButton_7->setBackgroundIcon(icon);
        ui->pushButton_8->setAutoFillBackground(false);
        ui->pushButton_8->setBackgroundIcon(icon);
        ui->pushButton_9->setAutoFillBackground(false);
        ui->pushButton_9->setBackgroundIcon(icon);
        ui->pushButton_10->setAutoFillBackground(false);
        ui->pushButton_10->setBackgroundIcon(icon);
        ui->pushButton_11->setAutoFillBackground(false);
        ui->pushButton_11->setBackgroundIcon(icon);
        ui->pushButton_12->setAutoFillBackground(false);
        ui->pushButton_12->setBackgroundIcon(icon);
    } else {
        qDebug() << "Can not found button-background-32x32.png";
    }
*/
    QSignalMapper *buttonsSignalMapper = new QSignalMapper(this);
    connect(ui->pushButton_1, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->pushButton_1, ui->pushButton_1->objectName());
    connect(ui->pushButton_2, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->pushButton_2, ui->pushButton_2->objectName());
    connect(ui->pushButton_3, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->pushButton_3, ui->pushButton_3->objectName());
    connect(ui->pushButton_4, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->pushButton_4, ui->pushButton_4->objectName());
    connect(ui->pushButton_5, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->pushButton_5, ui->pushButton_5->objectName());
    connect(ui->pushButton_6, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->pushButton_6, ui->pushButton_6->objectName());

    connect(ui->pushButton_7, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->pushButton_7, ui->pushButton_7->objectName());
    connect(ui->pushButton_8, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->pushButton_8, ui->pushButton_8->objectName());
    connect(ui->pushButton_9, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->pushButton_9, ui->pushButton_9->objectName());
    connect(ui->pushButton_10, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->pushButton_10, ui->pushButton_10->objectName());
    connect(ui->pushButton_11, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->pushButton_11, ui->pushButton_11->objectName());
    connect(ui->pushButton_12, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->pushButton_12, ui->pushButton_12->objectName());

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

LightingsControl::~LightingsControl()
{
    qDebug() << "LightingsControl::~LightingsControl";
    delete ui;
}

void LightingsControl::changeEvent(QEvent *e)
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

void LightingsControl::OnButtonClicked(const QString &name)
{
    qDebug() << "LightingsControl::OnButtonClicked" << name;
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
    } else {
        QObjectList objs = ui->frame->children();
        for (int i = 0; i < objs.size(); i++) {
            if (QString("QPushButton") != objs[i]->metaObject()->className())
                continue;

            if (name == objs[i]->objectName())
                ui->lightLabel->setText(tr("Light #%1").arg(i));
            else
                (qobject_cast<QPushButton *>(objs[i]))->setChecked(false);
        }
    }
}



