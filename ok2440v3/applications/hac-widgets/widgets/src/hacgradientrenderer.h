#ifndef _HACGRADIENTRENDERER_H_
#define _HACGRADIENTRENDERER_H_

#include "hacwidgetglobal.h"

class HacGradientRendererPrivate;

class HACWIDGET_EXPORT HacGradientRenderer : public QPushButton {
	Q_OBJECT

public:
	HacGradientRenderer(QWidget *parent = 0);
	~HacGradientRenderer();

private:
	HacGradientRendererPrivate *d;
};

#endif // _HACGRADIENTRENDERER_H_
