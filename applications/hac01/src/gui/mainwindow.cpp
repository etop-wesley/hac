//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "roomchoose.h"
#include "autocontrolmain.h"
#include "stagecontrol.h"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags f)
:   QWidget(parent, f), ui(new Ui::MainWindow)
{
    qDebug() << "MainWindow::MainWindow";
    ui->setupUi(this);
    while (ui->stackedWidget->count() > 0)
        ui->stackedWidget->removeWidget(ui->stackedWidget->widget(0));

    readSettings();

    connect(ui->homeButton, SIGNAL(clicked()),  this, SLOT(OnHomeButtonClicked()));
    connect(ui->backButton, SIGNAL(clicked()),  this, SLOT(OnBackButtonClicked()));
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow::~MainWindow";
    writeSettings();
    delete ui;
}

void MainWindow::readSettings()
{
    qDebug() << "MainWindow::readSettings";

    // setup background
    QImage image(":/HAC01/desktop-wallpaper.png");
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

void MainWindow::writeSettings()
{
    qDebug() << "MainWindow::writeSettings";

}


void MainWindow::changeEvent(QEvent *e)
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

void MainWindow::OnHomeButtonClicked()
{
    qDebug() << "MainWindow::OnHomeButtonClicked";
    while (ui->stackedWidget->count() > 0) {
        QWidget *widget = ui->stackedWidget->currentWidget();
        ui->stackedWidget->removeWidget(widget);
        delete widget;
        widget = NULL;
    }

    hide();
}

void MainWindow::OnBackButtonClicked()
{
    qDebug() << "MainWindow::OnBackButtonClicked";
    if (ui->stackedWidget->count() > 0) {
        QWidget *widget = ui->stackedWidget->currentWidget();
        ui->stackedWidget->removeWidget(widget);
        delete widget;
        widget = NULL;
    }

    if (ui->stackedWidget->count() == 0)
        hide();
}

QWidget * MainWindow::showWidget(const QString &name)
{
    qDebug() << "HacMainWindow::showWindow" << name;
    QWidget *widget = NULL;
    for (int i = 0; i < ui->stackedWidget->count(); i++) {
        QWidget *w = ui->stackedWidget->widget(i);
        if (w->objectName() == name) {
            widget = w;
            break;
        }
    }

    if (widget == NULL) {
        if (name == "RoomChoose")
            widget = new RoomChoose;
        else if (name == "AutoControlMain")
            widget = new AutoControlMain;
        else if (name == "StageControl")
            widget = new StageControl;

        if (widget != NULL) {
            widget->setAttribute(Qt::WA_DeleteOnClose);
        }
    }

    if (widget != NULL) {
        ui->stackedWidget->addWidget(widget);
        ui->stackedWidget->setCurrentWidget(widget);
    }

    return widget;
}

