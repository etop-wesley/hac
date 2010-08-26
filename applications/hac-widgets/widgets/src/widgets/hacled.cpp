//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include "hacled.h"
#include <QPaintEvent>
#include <QPainter>
#include <QStyle>
#include <QStyleOption>
#include <QTimer>
#include <QGradient>
#include <QApplication>

class HacLedPrivate {
public:
    HacLedPrivate(HacLed *pub) {
        color = Qt::red;
        checked = false;
        width = 1;
        period = 1000;
        timer = -1;
        shape = HacLed::Circular;
    }
    QColor color;
    bool checked;
    int width;
    HacLed::Shape shape;
    int timer;
    int period;

private:

};

/*!
 * \class HacLed
 * \brief The HacLed class provides a widget that displays a LED.
 * \mainclass
 *
 * \inmodule wwWidgets
 *
 * \image HacLed.png
 *
 */

/*!
 *
 * \property    HacLed::checked
 * \brief  	Property keeping information whether the led is turned on
 */
/*!
 * \property    HacLed::animated
 * \brief  	Property keeping information whether the diode is animating
 * 
 */
/*!
 * \enum HacLed::Shape
 * \value Circular		round LED
 * \value RectangularSunken	rectangular LED with sunken appearance
 * \value RectangularRaised	rectangular LED with raised appearence
 * \value RectangularPlain	rectangular flat LED
 *
 */
/*!
 * \fn HacLed::clicked()
 * \brief Signal emitted when the diode is clicked
 */
/*!
 * \fn HacLed::toggled(bool checked)
 * \brief Signal emitted when the diode is toggled.
 *
 * \a checked carries the information about the current state of the diode.
 */
/*!
 * \fn HacLed::colorChanged(const QColor &color)
 * \brief Signal emitted when the color of the diode is changed to \a color.
 */

/*!
 * \brief Constructs a led widget with a given \a parent.
 * 
 */
HacLed::HacLed(QWidget *parent)
: QWidget(parent), d(new HacLedPrivate(this))
{
    QSizePolicy sp(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sp.setHeightForWidth(true);
    setSizePolicy(sp);
}

/*!
 * \internal
 */
HacLed::~HacLed()
{
}

/*!
 * \internal
 */
QSize HacLed::sizeHint() const
{
    if (d->shape == Circular)
        return QSize(25,25).expandedTo(QApplication::globalStrut());
    else
		return QSize(25,15).expandedTo(QApplication::globalStrut());
}

/*!
 * \brief Constructs a led widget of colour \a col and shape \a shap with a given \a parent.
 * 
 */
HacLed::HacLed(const QColor & col, HacLed::Shape shap, QWidget * parent)
: QWidget(parent), d(new HacLedPrivate(this))
{
    d->color = col;
    d->checked = true;
    d->shape = shap;
}

/*!
 * \brief Sets the colour for the checked diode
 * 
 */
void HacLed::setColor(const QColor & c)
{
    if (c==d->color)
		return;

    d->color = c;
    emit colorChanged(c);
    update();
}

/*!
 * \property HacLed::color
 * \brief This property holds the colour of the diode
 */
QColor HacLed::color() const
{
    return d->color;
}

/*!
 * \internal
 */
void HacLed::paintEvent(QPaintEvent * )
{
    QPainter p(this);
    QColor bgColor = palette().background().color();

    if (d->shape==Circular) {
        int sidesize = qMin(width(), height());
        p.setRenderHint(QPainter::Antialiasing);
        int rad = sidesize*0.45;
        QRect r = rect().adjusted((width()-sidesize)/2, (height()-sidesize)/2, -(width()-sidesize)/2, -(height()-sidesize)/2);
        QRadialGradient grad(rect().center(), rad, rect().center()-QPoint(sidesize*0.1, sidesize*0.1) );
        grad.setColorAt(0.0, palette().color(QPalette::Light));
        grad.setColorAt(0.75, isChecked() ? d->color : bgColor);
        p.setBrush(grad);
        QPen pe = p.pen();
        pe.setWidth(d->width);
        pe.setColor(palette().color(QPalette::Foreground));
        p.setPen(pe);

        p.drawEllipse(r.adjusted(d->width,d->width,-d->width,-d->width));
    } else { /*if (d->shape == Rectangular)*/
        QStyleOptionFrame opt;
        opt.initFrom(this);
        opt.lineWidth = d->width;
        opt.midLineWidth = d->width;
        if (d->shape==RectangularRaised)
            opt.state |= QStyle::State_Raised;
        else if (d->shape==RectangularSunken)
            opt.state |= QStyle::State_Sunken;
        QBrush br(isChecked() ? d->color : bgColor);
        if (d->shape==RectangularPlain)
            qDrawPlainRect(&p, opt.rect, opt.palette.foreground().color(), d->width, &br);
        else
            qDrawShadePanel(&p, opt.rect, opt.palette, d->shape==RectangularSunken, d->width, &br);
    }
}

/*!
 * \internal
 */
int HacLed::heightForWidth(int width) const
{
    if (d->shape!=Circular)
		return -1;
    return width;
}


bool HacLed::isChecked() const
{
    return d->checked;
}

/*!
 * \brief Sets the state of the diode.
 */
void HacLed::setChecked(bool checked)
{
    if (d->checked == checked)
		return;

    d->checked = checked;
    emit toggled(checked);
    update();
}

/*!
 * \property HacLed::shape
 * \brief This property holds the shape of the diode.
 */
HacLed::Shape HacLed::shape() const
{
    return d->shape;
}

/*!
 * Sets the shape of the diode.
 * 
 */
void HacLed::setShape(Shape s)
{
    if (s==d->shape)
		return;

	d->shape = s;
    updateGeometry();
    update();
}

/*!
 * \brief Toggles the diode on or off.
 */
void HacLed::toggle()
{
    setChecked(!isChecked());
}

/*!
 * \internal
 */
void HacLed::mouseReleaseEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton)
        emit clicked();
}

/*!
 * \property HacLed::frameWidth
 * \brief The width of led's frame
 */
int HacLed::frameWidth() const
{
	return d->width;
}

/*!
 * @brief Sets the width of led's frame
 * 
 */
void HacLed::setFrameWidth(int width)
{
    if (width == d->width) return;
    d->width = width;
    update();
}


bool HacLed::isAnimated() const
{
    return d->timer!=-1;
}

/*!
 * \property HacLed::period
 * \brief Blink period of the diode.
 */
int HacLed::period() const
{
    return d->period;
}

void HacLed::setAnimated(bool enable)
{
    if (enable && d->timer ==- 1) {
        d->timer = startTimer(d->period);
        update();
    } else if (!enable && d->timer != -1) {
        killTimer(d->timer);
        d->timer = -1;
        update();
    }
}

/*!
 * \internal
 */
void HacLed::timerEvent(QTimerEvent * event)
{
    if (event->timerId() != d->timer)
        return;

    toggle();
}

void HacLed::setPeriod(int period)
{
    if (period==d->period)
		return;

	d->period = period;
    if (isAnimated()) {
        killTimer(d->timer);
        d->timer = startTimer(d->period);
    }
}

/*!
 * \brief Blinks the diode once.
 */
void HacLed::blink()
{
    if (isAnimated())
		return;

    setChecked(true);
    QTimer::singleShot(100, this, SLOT(toggle()));
}


