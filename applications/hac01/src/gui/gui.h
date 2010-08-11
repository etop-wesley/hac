/*
 * HAC GUI configuration
 */
#ifndef _GUI_H_
#define _GUI_H_

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480



#define SCREEN_X 0
#define SCREEN_Y 0
#define SCREEN_W 800
#define SCREEN_H 480
#define TASKPANEL_X SCREEN_X
#define TASKPANEL_Y SCREEN_Y
#define TASKPANEL_W SCREEN_W
#define TASKPANEL_H 80
#define WINDOW_X SCREEN_X
#define WINDOW_Y SCREEN_Y+TASKPANEL_H
#define WINDOW_W SCREEN_W
#define WINDOW_H SCREEN_H-TASKPANEL_H

#define DEFAULT_POINTERCAL_FILE "/usr/etc/pointercal"

#endif // _GUI_H_
