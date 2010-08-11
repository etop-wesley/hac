#ifndef _AUTOCONTROLMAIN_H_
#define _AUTOCONTROLMAIN_H_

#include <QWidget>

namespace Ui {
	class AutoControlMain;
}

class QListWidgetItem;

class AutoControlMain : public QWidget {
	Q_OBJECT

public:
	AutoControlMain(QWidget *parent = NULL,  Qt::WindowFlags f = 0);
	~AutoControlMain();

    QString currentRoomName() const;

public Q_SLOTS:
    void setCurrentRoomName(const QString &);
    //void setCurrentRoomModel(const QString &);
    void setCurrentControlIndex(int index);

Q_SIGNALS:

protected:
	void changeEvent(QEvent *e);

private Q_SLOTS:
    #if 0
    void OnListWidgetItemClicked(QListWidgetItem *item);
    #else
    void OnButtonClicked(const QString &);
    #endif

private:
    void showControl(int index);

private:
	Ui::AutoControlMain *ui;
};

#endif // _AUTOCONTROLMAIN_H_
