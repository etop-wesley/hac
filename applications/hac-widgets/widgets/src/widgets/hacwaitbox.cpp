//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>

#include <QBoxLayout>
#include <QGridLayout>
#include <QSpacerItem>
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QDesktopWidget>
#include <QImageReader>
#include <QApplication>
#include "hacwaitbox.h"

#define BUSY_STYLE 3
#if BUSY_STYLE == 1
#define BUSY_INTERVAL 250 // ms
#define BUSY_ICON ":/hacwidgets/images/clock1.png"
#define BUSY_COUNT 60
#elif BUSY_STYLE == 2
#define BUSY_INTERVAL 250 // ms
#define BUSY_ICON ":/hacwidgets/images/clock2.png"
#define BUSY_COUNT 60
#elif BUSY_STYLE == 3
#define BUSY_INTERVAL 125 // ms
#define BUSY_ICON ":/hacwidgets/images/busy.png"
#define BUSY_COUNT 16
#define BUSY_ICON_WIDTH 64
#define BUSY_ICON_HEITHT 64
#elif BUSY_STYLE == 4
#define BUSY_INTERVAL 0 // ms
#define BUSY_ICON ":/hacwidgets/images/bigwait.png"
#define BUSY_COUNT 0
#endif

class ImageLabel : public QWidget {
	Q_OBJECT
public:
	ImageLabel(QWidget *parent);
	~ImageLabel();

public Q_SLOTS:
	void start() {
		if (timer != 0) { // stop timer firstly.
			killTimer(timer);
			timer = 0;
		}
		if (BUSY_INTERVAL >= 0)
			timer = startTimer(BUSY_INTERVAL);
	}

	void stop() {
		if (timer != 0) {
			killTimer(timer);
			timer = 0;
		}
		index = BUSY_COUNT / 2;
	}

	bool isActive() const{ return timer !=0; }
	void setActive(bool active) { active ? start() : stop(); }

	QSize sizeHint() const;

protected:
	void paintEvent(QPaintEvent *e);
	void timerEvent(QTimerEvent *e);

private:
	QPixmap busyIcon;
	int count;
	int index;
	int timer;
};

ImageLabel::ImageLabel(QWidget *parent)
: QWidget(parent), index(0), timer(0)
{
	//setAttribute(Qt::WA_OpaquePaintEvent, true);
	setAttribute(Qt::WA_NoSystemBackground, true);
	setAutoFillBackground(false);

	setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
	QImageReader imgReader(BUSY_ICON);
	QImage img = imgReader.read();
	busyIcon = QPixmap::fromImage(img);
#if BUSY_STYLE == 1 || BUSY_STYLE == 2 || BUSY_STYLE == 4
	count = BUSY_COUNT;
#elif BUSY_STYLE == 3
	count = busyIcon.width() / busyIcon.height();
#endif
}

ImageLabel::~ImageLabel()
{
	stop();
}

QSize ImageLabel::sizeHint() const
{
#if BUSY_STYLE == 1 || BUSY_STYLE == 2 || BUSY_STYLE == 4
	return busyIcon.size();
#elif BUSY_STYLE == 3
	return QSize(busyIcon.height(), busyIcon.height());
#endif
}

void ImageLabel::paintEvent(QPaintEvent *)
{
	QPainter p(this);
#if BUSY_STYLE == 1 || BUSY_STYLE == 2 || BUSY_STYLE == 4
	p.drawPixmap((width() - busyIcon.width())/2, (height() - busyIcon.height())/2, busyIcon);
#if BUSY_STYLE != 4
	p.setRenderHint(QPainter::Antialiasing, true);
	p.setPen(QPen(Qt::black, 2));
	p.translate(qreal(rect().width())/2.0, qreal(rect().height())/2.0);
	p.rotate(index * 360/BUSY_COUNT);
	p.drawLine(0, 0, 0, busyIcon.width()/2 - busyIcon.width()/8);
#endif
#elif BUSY_STYLE == 3
	p.drawPixmap((width() - busyIcon.height())/2, (height() - busyIcon.height())/2, busyIcon.copy(index*busyIcon.height(), 0, busyIcon.height(), busyIcon.height()));
#endif
}

void ImageLabel::timerEvent(QTimerEvent *e)
{
	if (e->timerId() == timer) {
		index ++;
		if (index >= count)
			index = 0;

		update();
		e->accept();
		return;
	}
	QWidget::timerEvent(e);
}

//===========================================================================

class HacWaitBoxPrivate {
public:
	HacWaitBox::WaitBoxStyles waitBoxStyles;
	QGridLayout *gridLayout;
	QHBoxLayout *horizontalLayout_1;
	QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_1;
    QSpacerItem *horizontalSpacer_2;

	QLabel *textLabel;
	ImageLabel *imageLabel;
	QPushButton *cancelButton;
	bool cancelEnabled;
	bool wasCancelled;
	int showDelayTId;
	int showDelayTime;
	int hideDelayTId;
	int hideDelayTime;
	int expiryTId;
	int expiryTime;
};

/*!
  Constructs an HacWaitBox object with the given \a parent and flag.
*/
HacWaitBox::HacWaitBox(QWidget *parent, Qt::WindowFlags f)
: QDialog(parent, f), d(new HacWaitBoxPrivate)
{
	qDebug() << "HacWaitBox::HacWaitBox";

	initPrivate();

	setModal(true);
	//setWindowFlags(Qt::SplashScreen);

	//setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_OpaquePaintEvent, true);
	setAttribute(Qt::WA_NoSystemBackground, true);
	setAutoFillBackground(false);

	reinitLayout();

	resize(sizeHint());
}

HacWaitBox::HacWaitBox(WaitBoxStyles styles, QWidget *parent, Qt::WindowFlags f)
: QDialog(parent, f), d(new HacWaitBoxPrivate)
{
	initPrivate();
	d->waitBoxStyles = styles;

	setModal(true);
	//setWindowFlags(Qt::SplashScreen);

	//setAttribute(Qt::WA_PaintOnScreen, true);
	setAttribute(Qt::WA_OpaquePaintEvent, true);
	setAttribute(Qt::WA_NoSystemBackground, true);
	setAutoFillBackground(false);

	reinitLayout();

	resize(sizeHint());

}

/*!
	Destroys a HacWaitBox
	*/
HacWaitBox::~HacWaitBox()
{
	qDebug() << "HacWaitBox::~HacWaitBox";

	delete d;
}

void HacWaitBox::initPrivate()
{
	d->waitBoxStyles = (WaitBoxStyles)(BothIconText | TextRightIcon | CancalButtonIfNeed);
	d->gridLayout = NULL;
	d->textLabel = NULL;
	d->imageLabel = NULL;
	d->cancelButton = NULL;
	d->cancelEnabled = false;
	d->wasCancelled = false;
	d->showDelayTId = 0;
	d->showDelayTime = 0;
	d->hideDelayTId = 0;
	d->hideDelayTime = 0;
	d->expiryTId = 0;
	d->expiryTime = 0;
}

void HacWaitBox::reinitLayout()
{
	qDebug() << "HacWaitBox::reinitLayout";

	bool needImage = true, needText = true, needCancel = false;
	Qt::Alignment textAlign = Qt::AlignHCenter | Qt::AlignVCenter;
	QBoxLayout::Direction dir = QBoxLayout::LeftToRight;

	switch (d->waitBoxStyles & 0x0F) {
	case IconOnly: needImage = true; needText = false; break;
	case TextOnly: needImage = false; needText = true; break;
	case BothIconText: needImage = true; needText = true; break;
	default: break;
	}

	switch (d->waitBoxStyles & 0xF0) {
	case TextLeftIcon: dir = QBoxLayout::RightToLeft; break;
	case TextRightIcon: dir = QBoxLayout::LeftToRight; break;
	case TextAboveIcon: dir = QBoxLayout::BottomToTop; break;
	case TextUnderIcon: dir = QBoxLayout::TopToBottom; break;
	default: break;
	}

	if ((d->waitBoxStyles & 0xF00) == CancalButtonIfNeed)
		needCancel = d->cancelEnabled;

	if (d->gridLayout == NULL) {
		d->gridLayout = new QGridLayout(this);
		d->horizontalLayout_1 = new QHBoxLayout();
		d->gridLayout->addLayout(d->horizontalLayout_1, 0, 0, 1, 1);
	}

	if (needImage && d->imageLabel == NULL) {
		d->imageLabel = new ImageLabel(this);
		QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
		sizePolicy.setHorizontalStretch(1);
		sizePolicy.setVerticalStretch(0);
		sizePolicy.setHeightForWidth(d->imageLabel->sizePolicy().hasHeightForWidth());
		d->imageLabel->setSizePolicy(sizePolicy);
		d->horizontalLayout_1->addWidget(d->imageLabel);
	} else if (!needImage && d->imageLabel != NULL) {
		d->horizontalLayout_1->takeAt(d->horizontalLayout_1->indexOf(d->imageLabel));
		delete d->imageLabel;
		d->imageLabel = NULL;
	}

	if (needText && d->textLabel == NULL) {
		d->textLabel = new QLabel(this);
		d->textLabel->setWordWrap(true);
		d->textLabel->setAlignment(textAlign);
		QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
		sizePolicy1.setHorizontalStretch(3);
		sizePolicy1.setVerticalStretch(0);
		sizePolicy1.setHeightForWidth(d->textLabel->sizePolicy().hasHeightForWidth());
		d->textLabel->setSizePolicy(sizePolicy1);
		d->textLabel->setAlignment(Qt::AlignCenter);
		d->horizontalLayout_1->addWidget(d->textLabel);
	} else if (!needText && d->textLabel != NULL) {
		d->horizontalLayout_1->takeAt(d->horizontalLayout_1->indexOf(d->textLabel));
		delete d->textLabel;
		d->textLabel = NULL;
	}

	if (needCancel && d->cancelButton == NULL) {
		d->horizontalLayout_2 = new QHBoxLayout();
		d->horizontalSpacer_1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		d->horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
		d->horizontalLayout_2->addItem(d->horizontalSpacer_1);
		d->cancelButton = new QPushButton(this);
		d->horizontalLayout_2->addWidget(d->cancelButton);
		d->horizontalLayout_2->addItem(d->horizontalSpacer_2);
		d->gridLayout->addLayout(d->horizontalLayout_2, 1, 0, 1, 1);
		connect(d->cancelButton, SIGNAL(clicked()), this, SLOT(OnCancelButtonClicked()));
	} else if (!needCancel && d->cancelButton != NULL) {
		disconnect(d->cancelButton, SIGNAL(clicked()), this, SLOT(OnCancelButtonClicked()));
		d->horizontalLayout_2->takeAt(0);
		d->horizontalLayout_2->takeAt(1);
		d->horizontalLayout_2->takeAt(2);
		d->gridLayout->takeAt(1);
		delete d->horizontalLayout_2;
		delete d->horizontalSpacer_1;
		delete d->horizontalSpacer_2;
		delete d->cancelButton;
		d->cancelButton = NULL;
	}
}

QSize HacWaitBox::sizeHint() const
{
	QRect desktopRect= QApplication::desktop()->availableGeometry();
	return QSize(desktopRect.width() * 2 / 3, desktopRect.height() / 3);
}


void HacWaitBox::paintEvent(QPaintEvent *e)
{
	Q_UNUSED(e)

	QPainter p(this);
	QPalette pal = palette();
	p.fillRect(rect(), pal.brush(QPalette::Window));

	//p.setRenderHint(QPainter::Antialiasing, true);
	p.setPen(QPen(pal.color(QPalette::WindowText), 4));
	p.drawLine(0, 0, width(), 0);
	p.drawLine(width(), 0, width(), height());
	p.drawLine(width(), height(), 0, height());
	p.drawLine(0, height(), 0, 0);
}

HacWaitBox::WaitBoxStyles HacWaitBox::waitBoxStyle() const
{
	return d->waitBoxStyles;
}

void HacWaitBox::setWaitBoxStyle(HacWaitBox::WaitBoxStyles styles)
{
	if (styles == d->waitBoxStyles)
		return;
	d->waitBoxStyles = styles;
	reinitLayout();
	update();
}

/*!
	\property HacWaitBox::wasCancelled
	\brief indicates whether the widget was cancelled by the user when
	it was last shown.
*/

/*!
	Returns whether the widget was cancelled by the user when it was last
	shown.
 */
bool HacWaitBox::wasCancelled() const
{
	return d->wasCancelled;
}

/*!
	\property HacWaitBox::cancelEnabled
	\brief indicates whether the Cancel button appears on the context menu.
*/

/*!
	Sets whether the Cancel button appears on the context menu to \a enabled.
	When the Cancel button is presed the signal cancelled() is emitted.

	\sa cancelled()
*/
bool HacWaitBox::cancelEnabled() const
{
	return d->cancelEnabled;
}

void HacWaitBox::setCancelEnabled(bool enabled)
{
	if (enabled == d->cancelEnabled)
		return;
	d->cancelEnabled = enabled;
	reinitLayout();
	update();
}

QString HacWaitBox::cancelText() const
{
	if (d->cancelButton)
		return d->cancelButton->text();
	return QString();
}

void HacWaitBox::setCancelText(const QString &text)
{
	if (d->cancelButton)
		return d->cancelButton->setText(text);
}



/*!
  \fn void HacWaitBox::setText( const QString &text )

   Sets the informative text \a label for this wait widget.
*/
QString HacWaitBox::text() const
{
	if (d->textLabel != NULL)
		return d->textLabel->text();
	return QString();
}

void HacWaitBox::setText(const QString &text)
{
	if (d->textLabel != NULL)
		return d->textLabel->setText(text);
}

int HacWaitBox::showDelay() const
{
	return d->showDelayTime;
}

void HacWaitBox::setShowDelay(int msec)
{
	d->showDelayTime = msec;
}

int HacWaitBox::hideDelay() const
{
	return d->hideDelayTime;
}

void HacWaitBox::setHideDelay(int msec)
{
	d->hideDelayTime = msec;
}

/*!
	Hides the widget after \a msec.
*/
int HacWaitBox::expiry() const
{
	return d->expiryTime;
}

void HacWaitBox::setExpiry(int expiry)
{
	d->expiryTime = expiry;
}

/*! internal
 * start/stop my timer
 * @param timer: custom timer type, see below define.
 * @param enable: true for start, false for stop
 * @return: return if the timer is success be started or stoped.
 */
#define DELAY_SHOW_TIMER 1
#define DELAY_HIDE_TIMER 2
#define EXPIRY_TIMER 3
bool HacWaitBox::activeTimer(int timer, bool active)
{
	qDebug() << "HacWaitBox::activeTimer" << timer << active;
	int tId = -1;
	int time = -1;
	bool ret = false;
	switch (timer) {
	case DELAY_SHOW_TIMER:
		tId = d->showDelayTId;
		time = d->showDelayTime;
		break;
	case DELAY_HIDE_TIMER:
		tId = d->hideDelayTId;
		time = d->hideDelayTime;
		break;
	case EXPIRY_TIMER:
		tId = d->expiryTId;
		time = d->expiryTime;
		break;
	default:
		break;
	}

	if (tId == -1)
		return false;

	if (active) { // start timer
		if (tId != 0) {
			killTimer(tId);
			tId = 0;
		}
		if (time != 0) {
			tId = startTimer(time);
			ret = tId != 0;
		}
	} else { // stop timer
		if (tId != 0) {
			killTimer(tId);
			tId = 0;
		}
		ret = true;
	}

	switch (timer) {
	case DELAY_SHOW_TIMER:
		d->showDelayTId = tId;
		d->showDelayTime = time;
		break;
	case DELAY_HIDE_TIMER:
		d->hideDelayTId = tId;
		d->hideDelayTime = time;
		break;
	case EXPIRY_TIMER:
		d->expiryTId = tId;
		d->expiryTime = time;
		break;
	default:
		break;
	}

	return ret;
}

/*! internal
 * start/stop image label
 */
void HacWaitBox::activeImage(bool active)
{
	if (d->imageLabel != NULL)
		d->imageLabel->setActive(active);
}

/*! remp
 * show/hide HacWaitBox
 * all of the time out functions are got control by invoking this method,
 * or show()/hide() which call setVisible() internal.
 */
void HacWaitBox::setVisible(bool visible)
{
	if (visible) { // somebody called show()
		if (!activeTimer(DELAY_SHOW_TIMER, true)) {
			QDialog::setVisible(true);
			activeTimer(EXPIRY_TIMER, true);
			activeImage(true);
			d->wasCancelled = false;
		}
	} else { // somebody called hide()
		// stop show/expiry timer anyway.
		activeTimer(DELAY_SHOW_TIMER, false);
		activeTimer(EXPIRY_TIMER, false);
		if (!activeTimer(DELAY_HIDE_TIMER, true)) {
			activeImage(false);
			QDialog::setVisible(false);
		}
	}
}

void HacWaitBox::timerEvent(QTimerEvent *e)
{
	qDebug() << "HacWaitBox::timerEvent" << e->timerId();
	if (e->timerId() == d->showDelayTId) {
		qDebug() << "show delay time out";
		activeTimer(DELAY_SHOW_TIMER, false);
		QDialog::setVisible(true);
		activeImage(true);
		d->wasCancelled = false;
		activeTimer(EXPIRY_TIMER, true);
		e->accept();
		return;
	} else if (e->timerId() == d->hideDelayTId) {
		qDebug() << "hide delay time out";
		activeTimer(DELAY_HIDE_TIMER, false);
		activeImage(false);
		QDialog::setVisible(false);
		e->accept();
		return;
	} else if (e->timerId() == d->expiryTId) {
		qDebug() << "expiry time out";
		activeTimer(EXPIRY_TIMER, false);
		if (!activeTimer(DELAY_HIDE_TIMER, true)) {
			activeImage(false);
			QDialog::setVisible(false);
		}
		e->accept();
		return;
	} else {
		QDialog::timerEvent(e);
	}
}

/*!
  \reimp
*/
void HacWaitBox::done(int r)
{
	if (d->cancelEnabled && d->wasCancelled) {
        QDialog::done(r);
		emit cancelled();
	}
}

/*!
  \reimp
*/
void HacWaitBox::keyPressEvent( QKeyEvent *e )
{
	qDebug() << "HacWaitBox::keyPressEvent";

	if (e->key() == Qt::Key_Back && d->cancelEnabled) {
		d->wasCancelled = true;
		done(Cancelled);
	} else {
		e->accept();
	}
}

void HacWaitBox::OnCancelButtonClicked()
{
	qDebug() << "HacWaitBox::OnCancelButtonClicked";
	if (d->cancelEnabled) {
		d->wasCancelled = true;
        done(Cancelled);
	}
}

/*!
  \fn void HacWaitBox::cancelled()

  This signal is emitted whenever the wait widget dialog is cancelled by user.
*/

#include "hacwaitbox.moc"
