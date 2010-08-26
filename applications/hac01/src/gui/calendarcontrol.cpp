//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "calendarcontrol.h"
#include "ui_calendarcontrol.h"

CalendarControl::CalendarControl(QWidget *parent, Qt::WindowFlags f)
: QWidget(parent, f), ui(new Ui::CalendarControl)
{
	qDebug() << "CalendarControl::CalendarControl";
    ui->setupUi(this);

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

    connect(ui->daylyButton, SIGNAL(clicked()), this, SLOT(OnDaylyButtonClicked()));
    connect(ui->weeklyButton, SIGNAL(clicked()), this, SLOT(OnWeeklyButtonClicked()));
}

CalendarControl::~CalendarControl()
{
	qDebug() << "CalendarControl::~CalendarControl";
    delete ui;
}

void CalendarControl::changeEvent(QEvent *e)
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

void CalendarControl::OnDaylyButtonClicked()
{
	qDebug() << "CalendarControl::OnDaylyButtonClicked";

}

void CalendarControl::OnWeeklyButtonClicked()
{
	qDebug() << "CalendarControl::OnWeeklyButtonClicked";

}

