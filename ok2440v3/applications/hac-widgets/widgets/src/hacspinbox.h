#ifndef _HACSPINBOX_H_
#define _HACSPINBOX_H_

#if defined(QT_NO_SPINBOX)
#define HACWIDGETS_NO_SPINBOX
#endif

#if !defined(HACWIDGETS_NO_SPINBOX)


#include "hacwidgetglobal.h"
#include <QSpinBox>
#include <QStringList>

class HacSpinBoxPrivate;
class QLabel;

class HACWIDGET_EXPORT HacSpinBox : public QSpinBox
{
	Q_OBJECT

	Q_ENUMS(ContentType)
	Q_PROPERTY(ContentType contentType READ contentType WRITE setContentType)
    Q_PROPERTY(QStringList strings READ strings WRITE setStrings)

public:
	HacSpinBox(QWidget *parent = NULL);
	~HacSpinBox();

	enum ContentType {
		Content_Number = 0,
		Content_String
	};

	ContentType contentType() const;
	void setContentType(ContentType type);

    void setStrings(const QStringList &s);
    const QStringList & strings() const;

    virtual void stepBy(int steps);

Q_SIGNALS:
    void stringsChanged(const QStringList &);

protected:
    virtual QValidator::State validate(QString &text, int &pos) const;
	virtual QString	textFromValue(int value) const;
	virtual int	valueFromText(const QString &text) const;

private Q_SLOTS:
	void on_lineEdit_textChanged(const QString &);
	void on_timeLine_frameChanged(int);

private:
	void updateContent();

private:
	HacSpinBoxPrivate *d;
};

#endif // HACWIDGETS_NO_SPINBOX
#endif // _HACSPINBOX_H_
