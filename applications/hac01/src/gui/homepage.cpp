//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QTime>
#include <QPainter>

#include "homepage.h"
#include "ui_homepage.h"
#include "hacapplication.h"
#include "stagecontrol.h"
#include "roomchoose.h"
#include "calendarcontrol.h"

HomePage::HomePage(QWidget *parent,  Qt::WindowFlags f)
:   QWidget(parent, f), ui(new Ui::HomePage)
{
    qDebug() << "HomePage::HomePage";
    ui->setupUi(this);
/*
    QIcon icon;
    icon.addFile(":/HAC01/button1-normal.png", QSize(), QIcon::Normal);
    icon.addFile(":/HAC01/button1-active.png", QSize(), QIcon::Active);
   // ui->calendarButton->setAttribute(Qt::WA_OpaquePaintEvent, true);
   // ui->calendarButton->setAttribute(Qt::WA_NoSystemBackground, true);
    ui->calendarButton->setAutoFillBackground(false);
    ui->calendarButton->setBackgroundIcon(icon);
    ui->dateTimeLabel->setClickable(true);
*/

    ui->calendarButton->setPaletteBrushPanel(true);
    QPalette pal = ui->calendarButton->palette();
    pal.setBrush(QPalette::Button, QPixmap(":/hac01/images/button-background-normal-256x64.png"));
    pal.setBrush(QPalette::Light, QPixmap(":/hac01/images/button-background-active-256x64.png"));
    ui->calendarButton->setPalette(pal);

    connect(ui->menuListWidget, SIGNAL(itemClicked(QListWidgetItem *)),  this, SLOT(OnMenuListWidgetItemClicked(QListWidgetItem *)));
    connect(ui->calendarButton, SIGNAL(clicked()),  this, SLOT(OnCalendarButtonClicked()));

    readSettings();
}

HomePage::~HomePage()
{
    qDebug() << "HomePage::~HomePage";
    writeSettings();
    delete ui;
}

void HomePage::readSettings()
{
    qDebug() << "HomePage::readSettings";
	QImage image(":/hacwidgets/images/global-background-window.png");
	if (!image.isNull()) {
		QPalette palette;
		palette = this->palette();
		palette.setBrush(this->backgroundRole(), image); 
		this->setPalette(palette);
		this->setAutoFillBackground(true);
	} else {
		qDebug() << "can not find desktop background image";
	}

}

void HomePage::writeSettings()
{
    qDebug() << "HomePage::writeSettings";
}

void HomePage::changeEvent(QEvent *e)
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

void HomePage::OnMenuListWidgetItemClicked(QListWidgetItem *item)
{
    qDebug() << "HomePage::OnMenuListWidgetItemClicked" << item;
    HacApplication::processEvents(); // FIXME: should have a maximum time ?

    if (item == NULL)
        return;

    int row = ui->menuListWidget->row(item);
    // make sure the user doesn't click the menu by a strange way
    if (row != ui->menuListWidget->currentRow())
        return;
    qDebug() << "clicked row = " << row;

    QString name;
    switch (row) {
    case 0: name = "StageControl"; break;
    case 1: name = "RoomChoose"; break;
    case 2: break;
    case 3: break;
    case 4: break;
    default: break;
    }

    if (name.isEmpty())
        return;

	showWindow(name);
}

void HomePage::OnCalendarButtonClicked()
{
    qDebug() << "HomePage::OnCalendarButtonClicked";
	showWindow("CalendarControl");
}

void HomePage::showWindow(const QString &name)
{
    qDebug() << "HomePage::showWindow" << name;
    if (name.isEmpty())
        return;

	QWidget *window = HacApplication::findWindow(name);
	if (window == NULL) {
		if (name == "StageControl")
			window = new StageControl;
		else if (name == "RoomChoose")
			window = new RoomChoose;
		else if (name == "CalendarControl")
			window = new CalendarControl;

		if (window != NULL) {
			window->setAttribute(Qt::WA_DeleteOnClose, true);
		}
	}

	window->showMaximized();
}
