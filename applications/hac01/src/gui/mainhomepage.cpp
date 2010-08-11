//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QTime>
#include <QPainter>

#include "mainhomepage.h"
#include "ui_mainhomepage.h"
#include "mainwindow.h"
#include "hacapplication.h"

MainHomePage::MainHomePage(QWidget *parent,  Qt::WindowFlags f)
:   QWidget(parent, f), ui(new Ui::MainHomePage), mainWindow(NULL)
{
    qDebug() << "MainHomePage::MainHomePage";
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
    pal.setBrush(QPalette::Button, QPixmap(":/HAC01/button-background-normal-256x64.png"));
    pal.setBrush(QPalette::Light, QPixmap(":/HAC01/button-background-active-256x64.png"));
    ui->calendarButton->setPalette(pal);

    connect(ui->menuListWidget, SIGNAL(itemClicked(QListWidgetItem *)),  this, SLOT(OnMenuListWidgetItemClicked(QListWidgetItem *)));
    connect(ui->calendarButton, SIGNAL(clicked()),  this, SLOT(OnCalendarButtonClicked()));
    connect(ui->dateTimeLabel, SIGNAL(clicked()),  this, SLOT(OnDateTimeLabelClicked()));

    readSettings();
}

MainHomePage::~MainHomePage()
{
    qDebug() << "MainHomePage::~MainHomePage";
    writeSettings();
    if (mainWindow != NULL)
        delete mainWindow;
    delete ui;
}

void MainHomePage::readSettings()
{
    qDebug() << "MainHomePage::readSettings";

    // setup background
    QImage image(":/HAC01/desktop-wallpaper.png");
    if (!image.isNull()) {
        QPalette pal;
        pal = this->palette();
        pal.setBrush(this->backgroundRole(), image); 
        this->setPalette(pal);
        this->setAutoFillBackground(true);
    } else {
        qDebug() << "can not find desktop background image";
    }
}

void MainHomePage::writeSettings()
{
    qDebug() << "MainHomePage::writeSettings";

}

void MainHomePage::changeEvent(QEvent *e)
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

void MainHomePage::OnMenuListWidgetItemClicked(QListWidgetItem *item)
{
    qDebug() << "MainHomePage::OnMenuListWidgetItemClicked" << item;
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

    if (mainWindow == NULL) {
        mainWindow = new MainWindow;
        mainWindow->setAttribute(Qt::WA_DeleteOnClose); // FIXME: should be ?

        HacApp->setMainWindow(mainWindow);
    }

    if (mainWindow != NULL) {
        mainWindow->showWidget(name);
        mainWindow->showMaximized();
    }
}

void MainHomePage::OnCalendarButtonClicked()
{
    qDebug() << "MainHomePage::OnCalendarButtonClicked";

}

void MainHomePage::OnDateTimeLabelClicked()
{
    qDebug() << "MainHomePage::OnDateTimeLabelClicked";
}
