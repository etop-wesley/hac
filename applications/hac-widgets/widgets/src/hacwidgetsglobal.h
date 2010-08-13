
#ifndef _HACWIDGET_GLOBAL_H_
#define _HACWIDGET_GLOBAL_H_


//#define QT_NO_DEBUG_OUTPUT
#include <QDebug>
#include <QtCore/QtGlobal>

#if defined(Q_WS_WIN)
#ifdef HACWIDGETS_DLL
#if defined(HACWIDGETS_MAKEDLL) // create a hacwidgets library
#define HACWIDGET_EXPORT Q_DECL_EXPORT
#else // use a hacwidget library
#define HACWIDGET_EXPORT Q_DECL_IMPORT
#endif
#endif // HACWIDGETS_DLL
#endif // Q_WS_WIN

#ifndef HACWIDGET_EXPORT
#define HACWIDGET_EXPORT
#endif

/*!
  Some constants for use within HacWidgets.
*/
namespace HacWidgets
{

}; // HacWidgets

#endif // _HACWIDGET_GLOBAL_H_
