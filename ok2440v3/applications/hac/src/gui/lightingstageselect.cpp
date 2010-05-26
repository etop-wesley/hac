//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "lightingstageselect.h"
#include "ui_lightingstageselect.h"

LightingStageSelect::LightingStageSelect(QWidget *parent)
:	QWidget(parent),
    ui(new Ui::LightingStageSelect)
{
	qDebug() << "LightingStageSelect::LightingStageSelect";
    ui->setupUi(this);
}

LightingStageSelect::~LightingStageSelect()
{
	qDebug() << "LightingStageSelect::~LightingStageSelect";
    delete ui;
}

void LightingStageSelect::changeEvent(QEvent *e)
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

void LightingStageSelect::on_returnButton_clicked()
{
	qDebug() << "LightingStageSelect::on_returnButton_clicked";
	close();
}
