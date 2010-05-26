#ifndef _ACSCHEDULESET_H_
#define _ACSCHEDULESET_H_

#include <QWidget>

namespace Ui {
    class AcScheduleSet;
}

class QListWidgetItem;

class AcScheduleSet : public QWidget {
    Q_OBJECT
public:
    AcScheduleSet(QWidget *parent = 0);
    ~AcScheduleSet();

	void setTitle(const QString &text);

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    Ui::AcScheduleSet *ui;
};

#endif // _ACSCHEDULESET_H_
