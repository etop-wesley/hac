//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "statusbar.h"
#include "ui_statusbar.h"

StatusBar::StatusBar(QWidget *parent, Qt::WindowFlags f)
:	QWidget(parent, f),
    ui(new Ui::StatusBar)
{
	qDebug() << "StatusBar::StatusBar";

    ui->setupUi(this);
	ui->clockLabel ->setClickable(true);

	setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
/*

     setAutoFillBackground(false);
     setAttribute(Qt::WA_TranslucentBackground, true);
     QPalette pal = palette();
     pal.setColor(QPalette::Background, Qt::transparent);
     setPalette(pal);
*/

    //setWindowOpacity(0.7);

	QPixmap pixmap(":/hacwidgets/images/global-background-titlebar.png");
	if (!pixmap.isNull()) {
		QPalette palette;
		palette = this->palette();
		palette.setBrush(this->backgroundRole(), pixmap); 
		this->setPalette(palette);
		this->setAutoFillBackground(true);
	}

    ui->homeButton->setPaletteBrushPanel(true);
    QPalette pal = ui->homeButton->palette();
    pal.setBrush(QPalette::Button, QPixmap(":/hacserver/images/button2-home-normal-64x64.png"));
    pal.setBrush(QPalette::Light, QPixmap(":/hacserver/images/button-home-active-64x64.png"));
    ui->homeButton->setPalette(pal);


	connect(ui->homeButton, SIGNAL(clicked()), this, SIGNAL(homeClicked()));
	connect(ui->backButton, SIGNAL(clicked()), this, SIGNAL(backClicked()));
	connect(ui->clockLabel, SIGNAL(clicked()), this, SIGNAL(clockClicked()));
}

StatusBar::~StatusBar()
{
	qDebug() << "StatusBar::~StatusBar";
    delete ui;
}

void StatusBar::changeEvent(QEvent *e)
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

