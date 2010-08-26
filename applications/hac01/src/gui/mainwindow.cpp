//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags f)
:   QWidget(parent, f), ui(new Ui::MainWindow)
{
	qDebug() << "MainWindow::MainWindow";
	/* init UI */
	ui->setupUi(this);
	while (ui->stackedWidget->count() > 0)
		ui->stackedWidget->removeWidget(ui->stackedWidget->widget(0));
#ifdef HAC_PERFORMANCE_FIXUP
	ui->stackedWidget->setAttribute(Qt::WA_PaintOnScreen, true);
	//ui->stackedWidget->setAttribute(Qt::WA_OpaquePaintEvent, true);
	ui->stackedWidget->setAttribute(Qt::WA_NoSystemBackground, true);
	ui->stackedWidget->setAutoFillBackground(false);
#endif // HAC_PERFORMANCE_FIXUP

	/* setup from settings */
	readSettings();

	/* connect signals, we are ready to go! */
	connect(ui->homeButton, SIGNAL(clicked()),  this, SLOT(OnHomeButtonClicked()));
	connect(ui->backButton, SIGNAL(clicked()),  this, SLOT(OnBackButtonClicked()));
	connect(ui->stackedWidget, SIGNAL(currentChanged(int)),  this, SLOT(OnStackWidgetCurrentChanged(int)));
	connect(ui->stackedWidget, SIGNAL(widgetRemoved(int)),  this, SLOT(OnStackWidgetWidgetRemoved(int)));
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
	QImage image(":/hac01/images/desktop-wallpaper.png");
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
	while (ui->stackedWidget->count() > 1) {
		QWidget *widget = ui->stackedWidget->currentWidget();
		ui->stackedWidget->removeWidget(widget);
		delete widget;
		widget = NULL;
	}
}

void MainWindow::OnBackButtonClicked()
{
	qDebug() << "MainWindow::OnBackButtonClicked";
	if (ui->stackedWidget->count() > 1) {
		QWidget *widget = ui->stackedWidget->currentWidget();
		ui->stackedWidget->removeWidget(widget);
		delete widget;
		widget = NULL;
	}
}

void MainWindow::OnStackWidgetCurrentChanged(int index)
{
	qDebug() << "MainWindow::OnStackWidgetCurrentChanged" << index;
	ui->homeButton->setVisible(index != 0);
	ui->backButton->setVisible(index != 0);
}

void MainWindow::OnStackWidgetWidgetRemoved(int index)
{
	qDebug() << "MainWindow::OnStackWidgetWidgetRemoved" << index;

}

