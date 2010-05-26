
#ifndef _SCRIBBLEWIDGET_H_
#define _SCRIBBLEWIDGET_H_

#include <hacsettings-config.h>
#include <QLabel>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QImage>
#include <QPainter>

class HACSETTINGS_EXPORT ScribbleWidget : public QWidget
{
	Q_OBJECT

public:
	ScribbleWidget(QWidget *parent = 0);

	void resizeEvent(QResizeEvent *e);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *);

private:
	void drawLineTo(const QPoint &endPoint);

private:
	bool scribbling;
	QPoint lastPoint;
	QImage image;
};

#endif // _SCRIBBLEWIDGET_H_
