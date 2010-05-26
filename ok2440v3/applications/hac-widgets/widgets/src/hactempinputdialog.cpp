#include "hactempinputdialog.h"
#include "ui_hactempinputdialog.h"

HacTempInputDialog::HacTempInputDialog(QWidget *parent, Qt::WindowFlags f)
: QDialog(parent, f), ui(new Ui::HacTempInputDialog)
{
    ui->setupUi(this);
	d_tempVal = 25;
}

HacTempInputDialog::~HacTempInputDialog()
{
	delete ui;
}

void HacTempInputDialog::changeEvent(QEvent *e)
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

void HacTempInputDialog::setStart(const QString &text)
{
	ui->startLabel->setText(text);
}

void HacTempInputDialog::setEnd(const QString &text)
{
	ui->endLabel->setText(text);
}

int HacTempInputDialog::temp() const
{
	return d_tempVal;
}

void HacTempInputDialog::on_upButton_pressed()
{
	d_tempVal ++;
	ui->tempLabel->setText(QString::number(d_tempVal));
}

void HacTempInputDialog::on_downButton_pressed()
{
	d_tempVal --;
	ui->tempLabel->setText(QString::number(d_tempVal));
}



