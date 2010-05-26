//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QGridLayout>
#include <QButtonGroup>
#include <QToolButton>
#include "hacnumberpad.h"
#include "hacnumberpad_p.h"

HacNumberPad::HacNumberPad(QWidget *parent)
: QWidget(parent), d(new HacNumberPadPrivate)
{
	QGridLayout *l = new QGridLayout(this);
	l->setSpacing(2);
	l->setMargin(2);
	QButtonGroup *group = new QButtonGroup(this);
	for (int i=0;i<9;i++) {
		QToolButton *b = new QToolButton;
		b->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
		b->setObjectName(QString("b%1").arg(i+1));
		b->setText(QString::number(i+1));
		l->addWidget(b, i/3, i%3);
		group->addButton(b, i+1);
	}
	QToolButton *b = new QToolButton;
	b->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	b->setObjectName("b0");
	b->setText("0");
	l->addWidget(b, 3, 1);
	group->addButton(b, 0);

	b = new QToolButton;
	b->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	b->setObjectName("bAster");
	b->setText("*");
	l->addWidget(b, 3, 0);
	group->addButton(b, 10);

	b = new QToolButton;
	b->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	b->setText("#");
	b->setObjectName("bHash");
	l->addWidget(b, 3, 2);
	group->addButton(b, 11);
	connect(group, SIGNAL(buttonClicked(int)), SLOT(OnButtonClicked(int)));
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

HacNumberPad::~HacNumberPad()
{
	if (d != NULL) {
		delete d;
		d = NULL;
	}
}

void HacNumberPad::animateClick(const QString & button, int msec) {
	if (button.size()!=1) return;
	char key = button[0].toAscii();
	QList<QToolButton*> items;
	QString name;
	switch (key) {
	case '#':
		name = "bHash";
		break;
	case '*':
		name = "bAster";
		break;
	default:
		name = QString("b%1").arg(key);
	}
	QToolButton *buttonPtr = qFindChild<QToolButton*>(this, name);
	if (!buttonPtr)	return;
	buttonPtr->animateClick(msec);
}

void HacNumberPad::OnButtonClicked(int id)
{
	if (id>=0 && id<10) {
		emit numberClicked(id);
		emit keyClicked(QString::number(id));
		return;
	}
	if (id==10) {
		emit asteriskClicked();
		emit keyClicked("*");
		return;
	}
	if (id==11) {
		emit hashClicked();
		emit keyClicked("#");
		return;
	}
}


HacNumberPadPrivate::HacNumberPadPrivate()
{
}

HacNumberPadPrivate::~HacNumberPadPrivate()
{
}
