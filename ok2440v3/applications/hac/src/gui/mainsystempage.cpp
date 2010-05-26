//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QPalette>
#include <QListWidgetItem>
#include "mainsystempage.h"
#include "ui_mainsystempage.h"
#include "fansettings.h"
#include "heatingsettings.h"
#include "passwordquerydialog.h"

MainSystemPage::MainSystemPage(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::MainSystemPage)
{
	qDebug() << "MainSystemPage::MainSystemPage";
	
    ui->setupUi(this);
	readSettings();
}

MainSystemPage::~MainSystemPage()
{
	qDebug() << "MainSystemPage::~MainSystemPage";

	writeSettings();
    delete ui;
}

void MainSystemPage::changeEvent(QEvent *e)
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

void MainSystemPage::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
	qDebug() << "MainSystemPage::on_listWidget_itemDoubleClicked";
	if (item == NULL)
		return;

	switch (ui->listWidget->row(item)) {
	case 0: // Home
		break;
	case 1: // Fan
		{
			FanSettings *w = new FanSettings;
			w->setAttribute(Qt::WA_DeleteOnClose, true);
			w->showMaximized();
		}
		break;
	case 2: // Heating
		{
			HeatingSettings *w = new HeatingSettings;
			w->setAttribute(Qt::WA_DeleteOnClose, true);
			w->showMaximized();
		}
		break;
	case 3: // Lighting
		break;
	case 4: // Switch
		break;
	case 5: // General
		break;
	case 6: // Update
		break;
	case 7: // Engineering
		{
			PasswordQueryDialog *pwDialog = new PasswordQueryDialog;
			pwDialog->showMaximized();
			if (pwDialog->exec() == QDialog::Accepted) {
				// continue ...
			}
			delete pwDialog;
		}
		break;
	default:
		break;
	}
}

void MainSystemPage::readSettings()
{
	qDebug() << "MainSystemPage::readSettings";
}

void MainSystemPage::writeSettings()
{
	qDebug() << "MainSystemPage::writeSettings";
}

