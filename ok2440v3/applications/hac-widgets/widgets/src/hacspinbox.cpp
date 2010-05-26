#include "hacspinbox.h"
#if !defined(HACWIDGETS_NO_SPINBOX)
#include "hacspinbox_p.h"
#include <QLineEdit>
#include <QTimeLine>
#include "haclineedit.h"

HacSpinBox::HacSpinBox(QWidget *parent)
: QSpinBox(parent), d(new HacSpinBoxPrivate)
{
	qDebug() << "HacSpinBox::HacSpinBox11";
	d->lineEdit = new HacLineEdit(this);
	setLineEdit(d->lineEdit);
	setContentType(Content_Number);

	//connect(lineEdit(), SIGNAL(textChanged(const QString &)), this, SLOT(on_lineEdit_textChanged(const QString &)));
	connect(this, SIGNAL(valueChanged(const QString &)), this, SLOT(on_lineEdit_textChanged(const QString &)));
}

HacSpinBox::~HacSpinBox()
{
	qDebug() << "HacSpinBox::~HacSpinBox";
	if (d != NULL) {
		delete d;
		d = NULL;
	}
}

HacSpinBox::ContentType HacSpinBox::contentType() const
{
	qDebug() << "HacSpinBox::contentType";

	return d->contentType;
}

void HacSpinBox::setContentType(ContentType type)
{
	qDebug() << "HacSpinBox::setContentType" << type;

	if (type == d->contentType)
		return;

	d->contentType = type;
	updateContent();
}

void HacSpinBox::setStrings(const QStringList &strings)
{
	qDebug() << "HacSpinBox::setStrings" << strings;

	if (strings == d->strings)
		return;

	d->strings = strings;
	updateContent();
}

const QStringList & HacSpinBox::strings() const
{
	return d->strings;
}

QString HacSpinBox::textFromValue(int value) const
{
	qDebug() << "HacSpinBox::textFromValue" << value;

	switch (d->contentType) {
	default:
	case Content_Number:
		return QSpinBox::textFromValue(value);
	case Content_String:
		if (d->strings.size() <= value)
			return "";
		return d->strings.at(value);
	}
}

int HacSpinBox::valueFromText(const QString &text) const
{
	qDebug() << "HacSpinBox::valueFromText" << text;
	switch (d->contentType) {
	default:
	case Content_Number:
		return QSpinBox::valueFromText(text);
	case Content_String:
		return d->strings.indexOf(text);
	}
}

QValidator::State HacSpinBox::validate(QString &input, int &pos) const
{
	qDebug() << "HacSpinBox::validate" << input << pos;

	switch (d->contentType) {
	default:
	case Content_Number:
		return QSpinBox::validate(input, pos);
	case Content_String:
		foreach(QString str, d->strings) {
			if (str==input)	return QValidator::Acceptable;
			if (str.contains(input)) return QValidator::Intermediate;
		}
		return QValidator::Invalid;
	}
}

void HacSpinBox::updateContent()
{
	qDebug() << "HacSpinBox::updateContent";

	switch (d->contentType) {
	default:
	case Content_Number:
		interpretText();
		break;
	case Content_String:
		setRange(0, d->strings.size() - 1);
		emit stringsChanged(d->strings);
		interpretText();
		break;
	}
}

void HacSpinBox::on_lineEdit_textChanged(const QString &text)
{
	return;
	qDebug() << "HacSpinBox::on_lineEdit_textChanged" << text;
	if (d->timeLine == NULL) {
		d->timeLine = new QTimeLine(5000, this);
		d->timeLine->setUpdateInterval(500);
		d->timeLine->setCurrentTime(0);
		d->timeLine->setLoopCount(0);
		d->timeLine->setFrameRange(0, 10);
		//d->timeLine.setDuration(d->timeLine.updateInterval() * (d->timeLine.endFrame() - d->timeLine.startFrame())/d->textAnimationStep);
		connect(d->timeLine, SIGNAL(frameChanged(int)), this, SLOT(on_timeLine_frameChanged(int)));
	}

	d->timeLine->start();
}

void HacSpinBox::on_timeLine_frameChanged(int frame)
{
	qDebug() << "HacSpinBox::on_timeLine_frameChanged" << frame;
	lineEdit()->setText(QString::number(frame));
}


void HacSpinBox::stepBy(int steps)
{
	qDebug() << "HacSpinBox::stepBy" << steps;
	setValue(value() + steps);
}

/*
 * internal
 */
HacSpinBoxPrivate::HacSpinBoxPrivate()
{
	timeLine = NULL;
	lineEdit = NULL;
}

/*
 * internal
 */
HacSpinBoxPrivate::~HacSpinBoxPrivate()
{
}

#endif // HACWIDGETS_NO_SPINBOX
