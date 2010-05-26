
#include "haclistnavigator.h"
#include "haclistnavigator_p.h"

#include <QLayout>
#include <QToolButton>
#include <QSlider>
#include <QtDebug>
#include <QMessageBox>
#include <QScrollBar>



void HacListNavigator::_q_valueChanged(int v) {
//     if (((QSlider*)widgets[HacListNavigator::Slider])->value()==v) return;
    ((QSlider*)d->widgets[HacListNavigator::Slider])->setValue(v);
    d->widgets[HacListNavigator::LastButton]->setEnabled(value()!= maximum() &&  minimum()!= maximum());
    d->widgets[HacListNavigator::FirstButton]->setEnabled(value()!= minimum() &&  minimum()!= maximum());
    d->widgets[HacListNavigator::NextButton]->setEnabled(value()!= maximum() &&  minimum()!= maximum());
    d->widgets[HacListNavigator::PrevButton]->setEnabled(value()!= minimum() &&  minimum()!= maximum());
}

void HacListNavigator::_q_updateLWRange() {
    if (!d->listWidget){ setRange(0,0); return; }
    setRange(0, d->listWidget->count()-1);
    setValue(d->listWidget->currentRow());
}

void HacListNavigator::_q_disconnectListWidget() {
    d->listWidget = 0;
}


HacListNavigator::HacListNavigator(QWidget * parent)
: QAbstractSlider(parent), d(new HacListNavigatorPrivate)
{
    setOrientation(Qt::Horizontal);
    d->buttons = (Buttons)(FirstButton|PrevButton|Slider|NextButton|LastButton);
    QHBoxLayout *l = new QHBoxLayout(this);
    l->setMargin(0);
    QToolButton *fir = new QToolButton;
    fir->setText(tr("First"));
    fir->setIcon(QPixmap(":/HacWidgets/go-first.png"));
    //fir->setToolTip(tr("Go to first"));
    fir->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    l->addWidget(fir);
    QToolButton *pre = new QToolButton;
    pre->setText("Previous");
    pre->setIcon(QPixmap(":/HacWidgets/go-previous.png"));
    //pre->setToolTip(tr("Go to previous"));
    pre->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    pre->setAutoRepeat(true);
    l->addWidget(pre);
    //l->addStretch();
    QSlider *sli = new QSlider(Qt::Horizontal);
    sli->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    connect(sli, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
    connect(this, SIGNAL(valueChanged(int)), sli, SLOT(setValue(int)));
    l->addWidget(sli);
    QToolButton *nex = new QToolButton;
    nex->setText("Next");
    nex->setIcon(QPixmap(":/HacWidgets/go-next.png"));
    //nex->setToolTip(tr("Go to next"));
    nex->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    nex->setAutoRepeat(true);
    l->addWidget(nex);
    QToolButton *las = new QToolButton;
    las->setText("Last");
    las->setIcon(QPixmap(":/HacWidgets/go-last.png"));
    //las->setToolTip(tr("Go to last"));
    las->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    l->addWidget(las);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    d->widgets[Slider] = sli;
    d->widgets[FirstButton] = fir;
    d->widgets[PrevButton] = pre;
    d->widgets[NextButton] = nex;
    d->widgets[LastButton] = las;
    d->widgets[FirstButton]->setVisible(false);
    d->widgets[LastButton]->setVisible(false);
    connect(fir, SIGNAL(clicked()), this, SLOT(toFirst()));
    connect(pre, SIGNAL(clicked()), this, SLOT(toPrevious()));
    connect(nex, SIGNAL(clicked()), this, SLOT(toNext()));
    connect(las, SIGNAL(clicked()), this, SLOT(toLast()));
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(_q_valueChanged(int)));
    _q_valueChanged(value());

	setButtons((HacListNavigator::Buttons)(HacListNavigator::FirstButton|HacListNavigator::PrevButton|HacListNavigator::Slider|HacListNavigator::NextButton|HacListNavigator::LastButton));
}

HacListNavigator::Buttons HacListNavigator::buttons() const {
    return d->buttons;
}

void HacListNavigator::setButtons(HacListNavigator::Buttons b) {
    if (d->buttons == b) return;
    d->buttons = b;
    foreach(Button bu, d->widgets.keys()) {
        d->widgets[bu]->setVisible(d->buttons & bu);
    }
}

void HacListNavigator::sliderChange(SliderChange change) {
    _q_valueChanged(value());
    if (change==SliderRangeChange) {
        ((QSlider*)d->widgets[Slider])->setRange(minimum(), maximum());
    }
    if (change==SliderStepsChange) {
        ((QSlider*)d->widgets[Slider])->setSingleStep(singleStep());
        ((QSlider*)d->widgets[Slider])->setPageStep(pageStep());
    }
    if (change==SliderOrientationChange) {
        QBoxLayout *l = 0;
        QLayout *old = layout();
        old->removeWidget(d->widgets[FirstButton]);
        old->removeWidget(d->widgets[PrevButton]);
        old->removeWidget(d->widgets[Slider]);
        old->removeWidget(d->widgets[NextButton]);
        old->removeWidget(d->widgets[LastButton]);
        delete layout();
        switch (orientation()) {
        case Qt::Horizontal:
            l = new QHBoxLayout(this);
            ((QSlider*)d->widgets[Slider])->setInvertedAppearance(false);
            ((QSlider*)d->widgets[Slider])->setInvertedControls(false);
            ((QToolButton*)d->widgets[FirstButton])->setIcon(QPixmap(":/HacWidgets/go-first.png"));
            ((QToolButton*)d->widgets[PrevButton])->setIcon(QPixmap(":/HacWidgets/go-previous.png"));
            ((QToolButton*)d->widgets[NextButton])->setIcon(QPixmap(":/HacWidgets/go-next.png"));
            ((QToolButton*)d->widgets[LastButton])->setIcon(QPixmap(":/HacWidgets/go-last.png"));
            break;
        case Qt::Vertical:
            l = new QVBoxLayout(this);
            ((QSlider*)d->widgets[Slider])->setInvertedAppearance(true);
            ((QSlider*)d->widgets[Slider])->setInvertedControls(true);
            ((QToolButton*)d->widgets[FirstButton])->setIcon(QPixmap(":/HacWidgets/go-top.png"));
            ((QToolButton*)d->widgets[PrevButton])->setIcon(QPixmap(":/HacWidgets/go-up.png"));
            ((QToolButton*)d->widgets[NextButton])->setIcon(QPixmap(":/HacWidgets/go-down.png"));
            ((QToolButton*)d->widgets[LastButton])->setIcon(QPixmap(":/HacWidgets/go-bottom.png"));
            break;
        }
        QSizePolicy sp = sizePolicy();
        sp.transpose();
        setSizePolicy(sp);
        l->setMargin(0);
        l->addWidget(d->widgets[FirstButton]);
        l->addWidget(d->widgets[PrevButton]);
        l->addWidget(d->widgets[Slider]);
        l->addWidget(d->widgets[NextButton]);
        l->addWidget(d->widgets[LastButton]);
        ((QSlider*)d->widgets[Slider])->setOrientation(orientation());
        resize(sizeHint());
    }
    QAbstractSlider::sliderChange(change);
}

/*!
 * \brief Sets the orientation of the widget.
 * 
 */
void HacListNavigator::setOrientation(Qt::Orientation o) {
    if (orientation()==o) return;
    QAbstractSlider::setOrientation(o);
    sliderChange(SliderOrientationChange);
}

bool HacListNavigator::autoRaise() const {
    if (!d->widgets.contains(FirstButton)) return false;
    return ((QToolButton*)d->widgets[FirstButton])->autoRaise();
}

void HacListNavigator::setAutoRaise(bool v) {
    if (autoRaise()==v) return;
    ((QToolButton*)d->widgets[FirstButton])->setAutoRaise(v);
    ((QToolButton*)d->widgets[PrevButton])->setAutoRaise(v);
    ((QToolButton*)d->widgets[NextButton])->setAutoRaise(v);
    ((QToolButton*)d->widgets[LastButton])->setAutoRaise(v);
}

void HacListNavigator::setToolButtonStyle(Qt::ToolButtonStyle v) {
    if (toolButtonStyle()==v) return;
    ((QToolButton*)d->widgets[FirstButton])->setToolButtonStyle(v);
    ((QToolButton*)d->widgets[PrevButton])->setToolButtonStyle(v);
    ((QToolButton*)d->widgets[NextButton])->setToolButtonStyle(v);
    ((QToolButton*)d->widgets[LastButton])->setToolButtonStyle(v);
}

Qt::ToolButtonStyle HacListNavigator::toolButtonStyle() const {
    if (!d->widgets.contains(FirstButton)) return Qt::ToolButtonIconOnly;
    return ((QToolButton*)d->widgets[FirstButton])->toolButtonStyle();
}

void HacListNavigator::toFirst() {
    if (value()==minimum()) return;
    setValue(minimum());
    emit first();
}

void HacListNavigator::toPrevious() {
    if (value()==minimum()) return;
    setValue(value()-1);
    emit previous();
}

void HacListNavigator::toLast() {
    if (value()>=maximum()) return;
    setValue(maximum());
    emit last();
}

void HacListNavigator::toNext() {
    if (value()>=maximum()) return;
    setValue(value()+1);
    emit next();
}

void HacListNavigator::setListWidget(QListWidget * lw) {
    if (d->listWidget) {
        disconnect(d->listWidget->model(), SIGNAL(rowsInserted(const QModelIndex&, int, int)), this, SLOT(_q_updateLWRange()));
        disconnect(d->listWidget->model(), SIGNAL(rowsRemoved(const QModelIndex&, int, int)), this, SLOT(_q_updateLWRange()));
        disconnect(d->listWidget->model(), SIGNAL(modelReset()), this, SLOT(_q_updateLWRange()));
        disconnect(d->listWidget, SIGNAL(destroyed()), this, SLOT(_q_disconnectListWidget()));
        disconnect(this, SIGNAL(valueChanged(int)), d->listWidget, SLOT(setCurrentRow(int)));
        disconnect(d->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(setValue(int)));
    }
    d->listWidget = lw;
    if (d->listWidget) {
        connect(d->listWidget->model(), SIGNAL(rowsInserted(const QModelIndex&, int, int)), this, SLOT(_q_updateLWRange()));
        connect(d->listWidget->model(), SIGNAL(rowsRemoved(const QModelIndex&, int, int)), this, SLOT(_q_updateLWRange()));
        connect(d->listWidget->model(), SIGNAL(modelReset()), this, SLOT(_q_updateLWRange()));
        connect(d->listWidget, SIGNAL(destroyed()), this, SLOT(_q_disconnectListWidget()));
        connect(this, SIGNAL(valueChanged(int)), d->listWidget, SLOT(setCurrentRow(int)));
        connect(d->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(setValue(int)));
    }
    _q_updateLWRange();
}

HacListNavigatorPrivate::HacListNavigatorPrivate()
{
}

HacListNavigatorPrivate::~HacListNavigatorPrivate()
{
}
