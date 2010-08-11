//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QScrollBar>
#include "roomchoose.h"
#include "ui_roomchoose.h"
#include "autocontrolmain.h"
#include "hacapplication.h"

RoomChoose::RoomChoose(QWidget *parent, Qt::WindowFlags f)
:	QWidget(parent, f), ui(new Ui::RoomChoose)
{
	qDebug() << "RoomChoose::RoomChoose";
    ui->setupUi(this);

    QImage image;
    image.load(":/HAC01/button2-background.png");
    if (!image.isNull()) {
        QPalette pal;
        pal = ui->prevButton->palette();
        pal.setBrush(QPalette::Button, image); 
        ui->prevButton->setPalette(pal);
        ui->prevButton->setAutoFillBackground(true);

        pal = ui->nextButton->palette();
        pal.setBrush(QPalette::Button, image); 
        ui->nextButton->setPalette(pal);
        ui->nextButton->setAutoFillBackground(true);
    }

    connect(ui->prevButton, SIGNAL(clicked()),  this, SLOT(OnPrevButtonClicked()));
    connect(ui->nextButton, SIGNAL(clicked()),  this, SLOT(OnNextButtonClicked()));
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem *)),  this, SLOT(OnListWidgetItemClicked(QListWidgetItem *)));
}

RoomChoose::~RoomChoose()
{
	qDebug() << "RoomChoose::~RoomChoose";
    delete ui;
}

void RoomChoose::changeEvent(QEvent *e)
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

void RoomChoose::OnPrevButtonClicked()
{
	qDebug() << "RoomChoose::OnPrevButtonClicked";
    QScrollBar *scrollBar = ui->listWidget->horizontalScrollBar();
    if (scrollBar != NULL)
        scrollBar->triggerAction(QAbstractSlider::SliderPageStepSub);
}

void RoomChoose::OnNextButtonClicked()
{
	qDebug() << "RoomChoose::OnNextButtonClicked";
    QScrollBar *scrollBar = ui->listWidget->horizontalScrollBar();
    if (scrollBar != NULL)
        scrollBar->triggerAction(QAbstractSlider::SliderPageStepAdd);
}

void RoomChoose::OnListWidgetItemClicked(QListWidgetItem *item)
{
	qDebug() << "RoomChoose::OnListWidgetItemClicked" << item;
    HacApplication::processEvents(); // FIXME: should have a maximum time ?

    if (item == NULL)
        return;

    int row = ui->listWidget->row(item);
    // make sure the user doesn't click the menu by a strange way
    if (row != ui->listWidget->currentRow())
        return;

    AutoControlMain *ctrl = qobject_cast<AutoControlMain *>(HacApp->mainWindow()->showWidget("AutoControlMain"));
    ctrl->setCurrentRoomName(item->text());
    ctrl->setCurrentControlIndex(0);
}

