//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "passwordquerydialog.h"
#include "ui_passwordquerydialog.h"

PasswordQueryDialog::PasswordQueryDialog(QWidget *parent, Qt::WindowFlags f)
:	QDialog(parent, f),
    ui(new Ui::PasswordQueryDialog)
{
	qDebug() << "PasswordQueryDialog::PasswordQueryDialog";
    ui->setupUi(this);

	connect(ui->numPad, SIGNAL(keyClicked(QString)), this, SLOT(on_numpad_keyClicked(QString)));
	connect(ui->numPad, SIGNAL(hashClicked()), this, SLOT(accept()));
	connect(ui->numPad, SIGNAL(asteriskClicked()), this, SLOT(reject()));
}

PasswordQueryDialog::~PasswordQueryDialog()
{
	qDebug() << "PasswordQueryDialog::~PasswordQueryDialog";
    delete ui;
}

QString PasswordQueryDialog::password() const
{
	return ui->lineEdit->text();
}

void PasswordQueryDialog::changeEvent(QEvent *e)
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

void PasswordQueryDialog::on_numpad_keyClicked(QString text)
{
	if (ui->lineEdit->text().size() >= 6)
		return;

	ui->lineEdit->insert(text);
}

