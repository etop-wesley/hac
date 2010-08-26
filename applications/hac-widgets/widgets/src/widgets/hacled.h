#ifndef _HACLED_H_
#define _HACLED_H_

/*
 * belowed from QwwLed of wwWidget project. 
 */

#include "hacwidgetsglobal.h"
#include <QtGui/QWidget>

class HacLedPrivate;

class HACWIDGET_EXPORT HacLed : public QWidget
{
	Q_OBJECT

	Q_ENUMS(Shape)
	Q_PROPERTY(QColor color READ color WRITE setColor)
	Q_PROPERTY(bool checked READ isChecked WRITE setChecked)
	Q_PROPERTY(Shape shape READ shape WRITE setShape)
	Q_PROPERTY(int frameWidth READ frameWidth WRITE setFrameWidth)
	Q_PROPERTY(bool animated READ isAnimated WRITE setAnimated)
	Q_PROPERTY(int period READ period WRITE setPeriod)

public:
	enum Shape {
		Circular, RectangularSunken, RectangularRaised, RectangularPlain
	};

	HacLed(QWidget *parent = NULL);
	HacLed(const QColor &col, Shape shap = Circular, QWidget *parent = NULL);
	~HacLed();

	QSize sizeHint() const;
	QColor color() const;
	bool isChecked() const;
	int heightForWidth(int w) const;
	Shape shape() const;
	int frameWidth() const;
	int period() const;
	bool isAnimated() const;

public Q_SLOTS:
	void setColor(const QColor &c);
	void setChecked(bool);
	void setShape(Shape);
	void toggle();
	void setFrameWidth(int);
	void setAnimated(bool);
	void setPeriod(int);
	void blink();

Q_SIGNALS:
	void colorChanged(const QColor &);
	void toggled(bool);
	void clicked();

protected:
	void paintEvent(QPaintEvent *pe);
	void mouseReleaseEvent(QMouseEvent *me);
	void timerEvent(QTimerEvent *te);

private:
	HacLedPrivate *d;
};

#endif // _HACLED_H_
