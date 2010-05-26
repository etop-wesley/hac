
#ifndef _CALIBRATIONDIALOG_H_
#define _CALIBRATIONDIALOG_H_

#include <hacsettings-config.h>
#include <QDialog>

#include <QWSPointerCalibrationData>

class HACSETTINGS_EXPORT CalibrationDialog : public QDialog
{
	Q_OBJECT
#if !defined(BUILD_HOST)

public:
    CalibrationDialog();
    ~CalibrationDialog();

    int exec();

protected:
    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void accept();

private:
    QWSPointerCalibrationData data;
    int pressCount;
#endif
};

#endif // _CALIBRATIONDIALOG_H_
