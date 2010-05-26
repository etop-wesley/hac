//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "mainlightingpage.h"
#include "ui_mainlightingpage.h"
#include "gui.h"
#include "hacapplication.h"
#include <QSignalMapper>
#include <QSettings>
#include <QPushButton>

#define SETTINGS_PATH "/usr/etc/hac01-config.ini"

MainLightingPage::MainLightingPage(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::MainLightingPage)
{
	qDebug() << "MainLightingPage::MainLightingPage";
	
	ui->setupUi(this);

	QSignalMapper *signalMapper = new QSignalMapper(this);

	QSettings settings(SETTINGS_PATH, QSettings::IniFormat);
	settings.beginGroup("UiConfig/MainLightingPage/TitleLabel");
	QString text = settings.value("Text").toString();
	if (!text.isEmpty())
		ui->titleLabel->setText(text);
	int font = settings.value("Font").toInt();
	if (font != 0) {
		QFont f = ui->titleLabel->font();
		f.setPointSize(font);
		ui->titleLabel->setFont(f);
	}
	settings.endGroup();
	settings.beginGroup("UiConfig/MainLightingPage/LightButtons");
	QStringList lightButtons = settings.childGroups();
	for (int i = 0; i < lightButtons.size(); i ++) {
		QPushButton *pushButton = new QPushButton(ui->scrollAreaWidgetContents);
		connect(pushButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
		signalMapper->setMapping(pushButton, 1);

		settings.beginGroup(lightButtons.at(i));
		QString text = settings.value("Text").toString();
		if (!text.isEmpty())
			pushButton->setText(text);
		int font = settings.value("Font").toInt();
		if (font != 0) {
			QFont f = pushButton->font();
			f.setPointSize(font);
			pushButton->setFont(f);
		}
		int width = settings.value("Width").toInt();
		if (width != 0)
			pushButton->setFixedWidth(width);
		int height = settings.value("Height").toInt();
		if (height != 0)
			pushButton->setFixedHeight(height);

		settings.endGroup();
		ui->gridLayout_2->addWidget(pushButton, i/3, i%3, 1, 1);
	}
	settings.endGroup();

	connect(signalMapper, SIGNAL(mapped(int)),
			this, SLOT(on_button_clicked(int)));
}

MainLightingPage::~MainLightingPage()
{
	qDebug() << "MainLightingPage::~MainLightingPage";
    delete ui;
}

void MainLightingPage::changeEvent(QEvent *e)
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

void MainLightingPage::on_button_clicked(int index)
{
	qDebug() << "MainLightingPage::on_button_clicked" << index;
	HacApp->showWindow("LightControlPage");

}


