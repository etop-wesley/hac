
#ifndef _CALIBRATIONDIALOG_H_
#define _CALIBRATIONDIALOG_H_

#include <hacsettingsglobal.h>
#include <QDialog>
#include <QWSPointerCalibrationData>

class HACSETTINGS_EXPORT CalibrationDialog : public QDialog
{
	Q_OBJECT

public:
    CalibrationDialog(QWidget * parent = NULL, Qt::WindowFlags f = 0);
    ~CalibrationDialog();

    int exec();

protected:
    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void accept();

private:
    QWSPointerCalibrationData data;
    int pressCount;
};

#endif // _CALIBRATIONDIALOG_H_
