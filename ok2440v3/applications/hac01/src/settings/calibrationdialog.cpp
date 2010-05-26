#include "calibrationdialog.h"

#include <QPainter>
#include <QFile>
#include <QTimer>
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QScreen>

#include <QWSServer>
#include <QWSPointerCalibrationData>

#if !defined(BUILD_HOST)

CalibrationDialog::CalibrationDialog()
{
    QRect desktop = QApplication::desktop()->geometry();
    desktop.moveTo(QPoint(0, 0));
    setGeometry(desktop);

    setFocusPolicy(Qt::StrongFocus);
    setFocus();
    setModal(true);

	int width = qt_screen->deviceWidth();
    int height = qt_screen->deviceHeight();

    int dx = width / 10;
    int dy = height / 10;

    QPoint *points = data.screenPoints;
    points[QWSPointerCalibrationData::TopLeft] = QPoint(dx, dy);
    points[QWSPointerCalibrationData::BottomLeft] = QPoint(dx, height - dy);
    points[QWSPointerCalibrationData::BottomRight] = QPoint(width - dx, height - dy);
    points[QWSPointerCalibrationData::TopRight] = QPoint(width - dx, dy);
    points[QWSPointerCalibrationData::Center] = QPoint(width / 2, height / 2);

	pressCount = 0;
}

CalibrationDialog::~CalibrationDialog()
{
}

int CalibrationDialog::exec()
{
    QWSServer::mouseHandler()->clearCalibration();
    grabMouse();
    activateWindow();
    int ret = QDialog::exec();
    releaseMouse();
    return ret;
}

void CalibrationDialog::paintEvent(QPaintEvent*)
{
	if (qt_screen == NULL)
		return;

	QPainter p(this);
    p.fillRect(rect(), Qt::white);

    QPoint point = data.screenPoints[pressCount];

    // Map to logical coordinates in case the screen is transformed
    QSize screenSize(qt_screen->deviceWidth(), qt_screen->deviceHeight());
    point = qt_screen->mapFromDevice(point, screenSize);

    p.fillRect(point.x() - 6, point.y() - 1, 13, 3, Qt::black);
    p.fillRect(point.x() - 1, point.y() - 6, 3, 13, Qt::black);
}

void CalibrationDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (qt_screen == NULL)
		return;

    // Map from device coordinates in case the screen is transformed
    QSize screenSize(qt_screen->width(), qt_screen->height());
    QPoint p = qt_screen->mapToDevice(event->pos(), screenSize);

    data.devPoints[pressCount] = p;

    if (++pressCount < 5)
        repaint();
    else
        accept();
}

void CalibrationDialog::accept()
{
    Q_ASSERT(pressCount == 5);
    QWSServer::mouseHandler()->calibrate(&data);
    QDialog::accept();
}
#endif


