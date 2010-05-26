#ifndef _CURTAINSCONTROLPAGE_H_
#define _CURTAINSCONTROLPAGE_H_

#include <QWidget>

namespace Ui {
    class CurtainsControlPage;
}

class CurtainsControlPage : public QWidget {
    Q_OBJECT
public:
    CurtainsControlPage(QWidget *parent = 0);
    ~CurtainsControlPage();

	void setBeUsedInStage();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:

private:

private:
    Ui::CurtainsControlPage *ui;
};

#endif // _CURTAINSCONTROLPAGE_H_
