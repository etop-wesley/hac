
#ifndef _HACANALOGCLOCKPICKWIDGET_H_
#define _HACANALOGCLOCKPICKWIDGET_H_

#include "hacwidgetglobal.h"
#include <QWidget>
#include <QTime>

class HacAnalogClockPickWidgetPrivate;

class HACWIDGET_EXPORT HacAnalogClockPickWidget : public QWidget
{
    Q_OBJECT

	Q_ENUMS(Precision);
	Q_PROPERTY(Precision precision READ precision WRITE setPrecision)
	Q_PROPERTY(bool textVisible READ isTextVisible WRITE setTextVisible)

public:
	HacAnalogClockPickWidget(QWidget *parent = 0);
   ~HacAnalogClockPickWidget();

	enum Precision {
		Precision_OneHour,
		Precision_HalfHour,
		Precision_QuarterHour
	};
	Precision precision() const;
	void setPrecision(Precision precision);

	bool isTextVisible() const;
	void setTextVisible(bool visible);

	class PickedItemData {
	public:
		inline PickedItemData() {}
		inline PickedItemData(const QTime &start, const QTime &end, int value)
		: d_start(start), d_end(end), d_value(value) {}
		inline PickedItemData(const PickedItemData &other)
		: d_start(other.d_start), d_end(other.d_end), d_value(other.d_value) {}

		inline ~PickedItemData() {}

		inline PickedItemData &operator=(const PickedItemData &other)
		{
			d_start = other.d_start;
			d_end = other.d_end;
			d_value = other.d_value;
			return *this;
		}

		inline bool operator==(const PickedItemData &other) const
		{
			return(d_start == other.d_start) && (d_end == other.d_end) && (d_value == other.d_value);
		}

		inline bool operator!=(const PickedItemData &other) const
		{
			return !(*this == other);
		}

		inline void setStart(const QTime &start) { d_start = start;}
		inline QTime start() const { return d_start;}

		inline void setEnd(const QTime &end) { d_end = end;}
		inline QTime end() const { return d_end;}

		inline void setValue(int value) { d_value = value;}
		inline int value() const { return d_value;}

	private:
		QTime d_start;
		QTime d_end;
		int d_value;
	};


	QList<PickedItemData> pickedList() const;
	void setPickedList(const QList<PickedItemData> &list);

protected:
	void paintEvent(QPaintEvent *event);
    void mouseDoubleClickEvent(QMouseEvent * e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

private:
	QTime timeFromPos(const QPoint &p);
	void checking_and_adding_item(const PickedItemData &item);

private:
	HacAnalogClockPickWidgetPrivate *d;
};

#endif // _HACANALOGCLOCKPICKWIDGET_H_
