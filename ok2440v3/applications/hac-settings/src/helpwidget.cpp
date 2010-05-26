//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "helpwidget.h"
#include "ui_helpwidget.h"

HelpWidget::HelpWidget(QWidget *parent)
:   QWidget(parent), ui(new Ui::HelpWidget)
{
	qDebug() << "HelpWidget::HelpWidget";
	ui->setupUi(this);
}

HelpWidget::~HelpWidget()
{
	qDebug() << "HelpWidget::~HelpWidget";
	delete ui;
}

void HelpWidget::setText(const QString &text)
{
	qDebug() << "HelpWidget::setText";
	ui->label->setText(text);
}

void HelpWidget::changeEvent(QEvent *e)
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

void HelpWidget::on_returnButton_pressed()
{
	qDebug() << "HelpWidget::on_returnButton_pressed";
	close();
}

