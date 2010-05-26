#ifndef _HACTEMPINPUTDIALOG_H_
#define _HACTEMPINPUTDIALOG_H_

#include <QDialog>

namespace Ui {
    class HacTempInputDialog;
}

class HacTempInputDialog : public QDialog {
    Q_OBJECT

public:
    HacTempInputDialog(QWidget * parent = 0, Qt::WindowFlags f = 0);
    ~HacTempInputDialog();

	void setStart(const QString &);
	void setEnd(const QString &);

	int temp() const;

public Q_SLOTS:

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
	void on_upButton_pressed();
	void on_downButton_pressed();

private:

private:
    Ui::HacTempInputDialog *ui;
	int d_tempVal;
};

#endif // _HACTEMPINPUTDIALOG_H_
