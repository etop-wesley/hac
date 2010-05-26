#ifndef _HACLISTNAVIGATOR_H_
#define _HACLISTNAVIGATOR_H_

#include "hacwidgetglobal.h"
#include <QAbstractSlider>
#include <QMap>

class HacListNavigatorPrivate;
class QListWidget;

class HACWIDGET_EXPORT HacListNavigator : public QAbstractSlider {
    Q_OBJECT
    Q_FLAGS(Buttons)
    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation);
    Q_PROPERTY(Buttons buttons READ buttons WRITE setButtons);
    Q_PROPERTY(bool autoRaise READ autoRaise WRITE setAutoRaise);
    Q_PROPERTY(Qt::ToolButtonStyle toolButtonStyle READ toolButtonStyle WRITE setToolButtonStyle);
public:
    enum Button {
        NoButtons = 0,
        FirstButton = 1,
        PrevButton = 2,
        Slider = 4,
        NextButton = 8,
        LastButton = 16
    };
    Q_DECLARE_FLAGS(Buttons, Button);
    HacListNavigator(QWidget *parent = 0);
    void setButtons(Buttons);
    Buttons buttons() const;
    bool autoRaise() const;
    Qt::ToolButtonStyle toolButtonStyle() const;
    void setListWidget(QListWidget *lw);

public Q_SLOTS:
    void setOrientation(Qt::Orientation o);
    void setAutoRaise(bool v);
    void setToolButtonStyle(Qt::ToolButtonStyle);
    void toFirst();
    void toLast();
    void toPrevious();
    void toNext();

Q_SIGNALS:
    void first();
    void previous();
    void next();
    void last();

protected:
    void sliderChange(SliderChange change);

private Q_SLOTS:
    void _q_valueChanged(int);
    void _q_updateLWRange();
    void _q_disconnectListWidget();
    void _q_first() {}
    void _q_next() {}
    void _q_previous() {}
    void _q_last() {}

private:
    HacListNavigatorPrivate *d;
};

#endif // _HACLISTNAVIGATOR_H_
