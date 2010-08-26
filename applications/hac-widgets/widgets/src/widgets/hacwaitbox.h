#ifndef _HACWAITBOX_H_
#define _HACWAITBOX_H_

/*
 * This class is imported from qt-extended-4.4.3 QWaitWidget
 * see src/libraries/qtopia/qwaitwidget.h, src/libraries/qtopia/qwaitwidget.cpp
 * for more details
 */

#include <QDialog>

#include <hacwidgetsglobal.h>

class HacWaitBoxPrivate;

class HACWIDGET_EXPORT HacWaitBox : public QDialog
{
    Q_OBJECT
	Q_ENUMS(WaitBoxStyle);
    Q_PROPERTY(WaitBoxStyles waitBoxStyle READ waitBoxStyle WRITE setWaitBoxStyle);
    Q_PROPERTY(bool wasCancelled READ wasCancelled);
    Q_PROPERTY(bool cancelEnabled READ cancelEnabled WRITE setCancelEnabled);
    Q_PROPERTY(QString cancelText READ cancelText WRITE setCancelText);
    Q_PROPERTY(QString text READ text WRITE setText);
    Q_PROPERTY(int showDelay READ showDelay WRITE setShowDelay);
    Q_PROPERTY(int hideDelay READ hideDelay WRITE setHideDelay);
    Q_PROPERTY(int expiry READ expiry WRITE setExpiry);

public:
	enum DialogCode { Cancelled = 2 };

    enum WaitBoxStyle {
        IconOnly = 0x01,
        TextOnly = 0x02,
		BothIconText = 0x03,

        TextLeftIcon = 0x10,
        TextRightIcon = 0x20,
        TextAboveIcon = 0x30,
        TextUnderIcon = 0x40,

		CancalButtonIfNeed = 0x100, // the cancel button is always show at the bottom center.
        FollowStyle // not implement, DON'T USE!
    };
	Q_DECLARE_FLAGS(WaitBoxStyles, WaitBoxStyle)

    explicit HacWaitBox(QWidget *parent = NULL, Qt::WindowFlags f = 0);
    HacWaitBox(WaitBoxStyles styles, QWidget *parent = NULL, Qt::WindowFlags f = 0);
    ~HacWaitBox();

    WaitBoxStyles waitBoxStyle() const;
    void setWaitBoxStyle(WaitBoxStyles style);

    bool wasCancelled() const;

    bool cancelEnabled() const;
    QString cancelText() const;
    QString text() const;
    int showDelay() const;
    int hideDelay() const;
    int expiry() const;

	QSize sizeHint() const;

public Q_SLOTS:
    void setCancelEnabled(bool enabled);
    void setCancelText(const QString &text);
    void setText(const QString &text);
    void setShowDelay(int msec);
    void setHideDelay(int msec);
    void setExpiry(int msec);

    void done(int r);

    void setVisible(bool visible);

Q_SIGNALS:
    void cancelled();

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);

private Q_SLOTS:
	void OnCancelButtonClicked();

private:
    void initPrivate();
    void reinitLayout();
    void activeImage(bool active);
    bool activeTimer(int timer, bool active);

private:
    HacWaitBoxPrivate *d;
};

#endif // _HACWAITBOX_H_

