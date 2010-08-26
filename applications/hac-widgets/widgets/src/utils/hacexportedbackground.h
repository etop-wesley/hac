
#ifndef _HACEXPORTEDBACKGROUND_H_
#define _HACEXPORTEDBACKGROUND_H_

/*
 * Imported from qt-extended-4.4.3 QExportedBackground class,
 * but remove the 'screen' property(the default screen is 0).
 */

#include <QObject>
#include <QSize>

class QPixmap;
class QColor;
class HacExportedBackgroundPrivate;

class HacExportedBackground : public QObject
{
    Q_OBJECT
public:
    explicit HacExportedBackground(QObject *parent = 0);
    ~HacExportedBackground();

    const QPixmap &background() const;
    bool isAvailable() const;

    static QSize exportedBackgroundSize();
    static void initExportedBackground(int width, int height);
    static void clearExportedBackground();
    static void setExportedBackgroundTint(int);
    static void setExportedBackground(const QPixmap &image);
    static void polishWindows();

Q_SIGNALS:
    void changed();
    void changed(const QPixmap &);

private Q_SLOTS:
    void sysMessage(const QString&,const QByteArray&);

private:
    void getPixmaps();

private:
    HacExportedBackgroundPrivate *d;
    friend class HacExportedBackgroundPrivate;
};

#endif // _HACEXPORTEDBACKGROUND_H_
