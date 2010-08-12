//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QSignalMapper>
#include "autocontrolmain.h"
#include "ui_autocontrolmain.h"
#include "hacapplication.h"
#include "accontrol.h"
#include "heatingcontrol.h"
#include "curtainscontrol.h"
#include "lightingscontrol.h"
#include "switchescontrol.h"

AutoControlMain::AutoControlMain(QWidget *parent, Qt::WindowFlags f)
:	QWidget(parent, f), ui(new Ui::AutoControlMain)
{
	qDebug() << "AutoControlMain::AutoControlMain";
    ui->setupUi(this);
    while (ui->stackedWidget->count() > 0)
        ui->stackedWidget->removeWidget(ui->stackedWidget->widget(0));
#ifdef HAC_PERFORMANCE_FIXUP
	ui->stackedWidget->setAttribute(Qt::WA_PaintOnScreen, true);
	//ui->stackedWidget->setAttribute(Qt::WA_OpaquePaintEvent, true);
	ui->stackedWidget->setAttribute(Qt::WA_NoSystemBackground, true);
	ui->stackedWidget->setAutoFillBackground(false);
#endif // HAC_PERFORMANCE_FIXUP

/*
    QIcon icon;
    icon.addFile(":/HAC01/button-background-black-normal-150x50.png", QSize(), QIcon::Normal);
    icon.addFile(":/HAC01/button-background-black-active-150x50.png", QSize(), QIcon::Active);
    if (!icon.isNull()) {
        ui->acButton->setAutoFillBackground(false);
        ui->acButton->setBackgroundIcon(icon);
        ui->heatingButton->setAutoFillBackground(false);
        ui->heatingButton->setBackgroundIcon(icon);
        ui->curtainsButton->setAutoFillBackground(false);
        ui->curtainsButton->setBackgroundIcon(icon);
        ui->lightingsButton->setAutoFillBackground(false);
        ui->lightingsButton->setBackgroundIcon(icon);
        ui->switchesButton->setAutoFillBackground(false);
        ui->switchesButton->setBackgroundIcon(icon);

    }
*/
    #if 0
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem *)),  this, SLOT(OnListWidgetItemClicked(QListWidgetItem *)));
    #else
    QSignalMapper *buttonsSignalMapper = new QSignalMapper(this);
    connect(ui->acButton, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->acButton, ui->acButton->objectName());
    connect(ui->heatingButton, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->heatingButton, ui->heatingButton->objectName());
    connect(ui->curtainsButton, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->curtainsButton, ui->curtainsButton->objectName());
    connect(ui->lightingsButton, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->lightingsButton, ui->lightingsButton->objectName());
    connect(ui->switchesButton, SIGNAL(clicked()), buttonsSignalMapper, SLOT(map()));
    buttonsSignalMapper->setMapping(ui->switchesButton, ui->switchesButton->objectName());
    connect(buttonsSignalMapper, SIGNAL(mapped(const QString &)), this, SLOT(OnButtonClicked(const QString &)));
    #endif
}

AutoControlMain::~AutoControlMain()
{
	qDebug() << "AutoControlMain::~AutoControlMain";
    delete ui;
}

void AutoControlMain::changeEvent(QEvent *e)
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

QString AutoControlMain::currentRoomName() const
{
    return ui->roomLabel->text();
}

void AutoControlMain::setCurrentRoomName(const QString &name)
{
    ui->roomLabel->setText(name);
}
#if 0
void AutoControlMain::setCurrentControlIndex(int index)
{
    ui->listWidget->setCurrentRow(index);
    showControl(index);
}

void AutoControlMain::OnListWidgetItemClicked(QListWidgetItem *item)
{
    qDebug() << "MainHomePage::OnListWidgetItemClicked" << item;
    HacApplication::processEvents(); // FIXME: should have a maximum time ?

    if (item == NULL)
        return;

    int row = ui->listWidget->row(item);
    // make sure the user doesn't click the menu by a strange way
    if (row != ui->listWidget->currentRow())
        return;
    qDebug() << "clicked row = " << row;

    showControl(row);
}
#else

void AutoControlMain::setCurrentControlIndex(int index)
{
    static QPushButton *buttons[] = {
        ui->acButton, ui->heatingButton, ui->curtainsButton, ui->lightingsButton, ui->switchesButton
    };

    for (int i = 0; i < 5; i++) {
        if (i == index) {
            buttons[i]->setChecked(true);
            OnButtonClicked(buttons[i]->objectName());
        }
    }
}

void AutoControlMain::OnButtonClicked(const QString &name)
{
    qDebug() << "AutoControlMain::OnButtonClicked" << name;

    int index = -1;
    if (name == "acButton") index = 0;
    else if (name == "heatingButton") index = 1;
    else if (name == "curtainsButton") index = 2;
    else if (name == "lightingsButton") index = 3;
    else if (name == "switchesButton") index = 4;

    static QPushButton *buttons[] = {
        ui->acButton, ui->heatingButton, ui->curtainsButton, ui->lightingsButton, ui->switchesButton
    };

    if (index == -1)
        return;

    for (int i = 0; i < 5; i++) {
        if (i != index)
            buttons[i]->setChecked(false);
    }

    showControl(index);
}

#endif

void AutoControlMain::showControl(int index)
{
    qDebug() << "HacMainWindow::showControl" << index;
    QString name;
    switch (index) {
    case 0: name = "AcControl"; break;
    case 1: name = "HeatingControl"; break;
    case 2: name = "CurtainsControl"; break;
    case 3: name = "LightingsControl"; break;
    case 4: name = "SwitchesControl"; break;
    default: break;
    }

    if (name.isEmpty())
        return;

    QWidget *widget = NULL;
    for (int i = 0; i < ui->stackedWidget->count(); i++) {
        QWidget *w = ui->stackedWidget->widget(i);
        if (w->objectName() == name) {
            widget = w;
            break;
        }
    }

    if (widget == NULL) {
        if (name == "AcControl")
            widget = new AcControl;
        else if (name == "HeatingControl")
            widget = new HeatingControl;
        else if (name == "CurtainsControl")
            widget = new CurtainsControl;
        else if (name == "LightingsControl")
            widget = new LightingsControl;
        else if (name == "SwitchesControl")
            widget = new SwitchesControl;

        if (widget != NULL) {
#ifdef HAC_PERFORMANCE_FIXUP
			widget->setAttribute(Qt::WA_PaintOnScreen, true);
            //widget->setAttribute(Qt::WA_OpaquePaintEvent, true);
			widget->setAttribute(Qt::WA_NoSystemBackground, true);
			widget->setAutoFillBackground(false);
#endif // HAC_PERFORMANCE_FIXUP
            widget->setAttribute(Qt::WA_DeleteOnClose);
        }
    }

    if (widget != NULL) {
        ui->stackedWidget->addWidget(widget);
        ui->stackedWidget->setCurrentWidget(widget);
    }
}


