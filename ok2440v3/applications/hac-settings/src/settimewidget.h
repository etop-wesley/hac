
#ifndef _SETTIMEWIDGET_H_
#define _SETTIMEWIDGET_H_

#include <hacsettings-config.h>
#include <QWidget>

namespace Ui {
    class SetTimeWidget;
}

class HACSETTINGS_EXPORT SetTimeWidget : public QWidget {
    Q_OBJECT

public:
    SetTimeWidget(QWidget *parent = NULL);
    ~SetTimeWidget();

Q_SIGNALS:
	void cancelled();
	void done();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_doneButton_pressed();
	void on_cancelButton_pressed();

private:

private:
    Ui::SetTimeWidget *ui;
};


#endif // _SETTIMEWIDGET_H_
