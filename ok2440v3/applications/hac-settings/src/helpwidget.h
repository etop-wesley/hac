
#ifndef _HELPWIDGET_H_
#define _HELPWIDGET_H_

#include <hacsettings-config.h>
#include <QWidget>
#include <QString>

namespace Ui {
    class HelpWidget;
}

class HACSETTINGS_EXPORT HelpWidget : public QWidget {
    Q_OBJECT

public:
    HelpWidget(QWidget *parent = NULL);
    ~HelpWidget();

	void setText(const QString &text);

Q_SIGNALS:

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_returnButton_pressed();

private:

private:
    Ui::HelpWidget *ui;
};

#endif // _HELPWIDGET_H_
