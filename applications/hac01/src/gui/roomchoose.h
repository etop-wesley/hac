#ifndef _ROOMCHOOSE_H_
#define _ROOMCHOOSE_H_

#include <QWidget>

namespace Ui {
	class RoomChoose;
}

class QListWidgetItem;

class RoomChoose : public QWidget {
	Q_OBJECT

public:
	RoomChoose(QWidget *parent = NULL,  Qt::WindowFlags f = 0);
	~RoomChoose();

public Q_SLOTS:

Q_SIGNALS:

protected:
	void changeEvent(QEvent *e);

private Q_SLOTS:
    void OnPrevButtonClicked();
    void OnNextButtonClicked();
    void OnListWidgetItemClicked(QListWidgetItem *item);

private:

private:
	Ui::RoomChoose *ui;
};

#endif // _ROOMCHOOSE_H_
