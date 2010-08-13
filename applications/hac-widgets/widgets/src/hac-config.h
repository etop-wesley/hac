#ifndef _HACCONFIG_H_
#define _HACCONFIG_H_

/*
 * HAC Global Configuration Definitions
 */

/* Config File Path */
#define CONFIG_PATH "/data"
#define CONFIG_FILE CONFIG_PATH"/hac"
#define POINTERCAL_FILE "/etc/pointercal"

/* GUI Define */
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480

#define SCREEN_X 0
#define SCREEN_Y 0
#define SCREEN_W SCREEN_WIDTH
#define SCREEN_H SCREEN_HEIGHT
#define TASKPANEL_X SCREEN_X
#define TASKPANEL_Y SCREEN_Y
#define TASKPANEL_W SCREEN_W
#define TASKPANEL_H 80
#define WINDOW_X SCREEN_X
#define WINDOW_Y SCREEN_Y+TASKPANEL_H
#define WINDOW_W SCREEN_W
#define WINDOW_H SCREEN_H-TASKPANEL_H

#endif // _HACHELP_H_
