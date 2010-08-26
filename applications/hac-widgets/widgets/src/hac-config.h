#ifndef _HACCONFIG_H_
#define _HACCONFIG_H_

/*
 * HAC Global Configuration Definitions
 */

/* Config File Path */
#define CONFIG_PATH "/data"
#define CONFIG_FILE CONFIG_PATH"/hac"
#define POINTERCAL_FILE "/etc/pointercal"

/* Applications */
#define APP_HACSERVER_BIN "/usr/bin/hacserver"
#define APP_HACSERVER_SCRIPT "/etc/init.d/hacserver"
#define APP_HAC01_BIN "/usr/bin/hac01"
#define APP_HAC01_SCRIPT "/etc/init.d/hac01"

/* GUI Define */
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480

#define SCREEN_X 0
#define SCREEN_Y 0
#define SCREEN_W SCREEN_WIDTH
#define SCREEN_H SCREEN_HEIGHT
#define STATUSBAR_X SCREEN_X
#define STATUSBAR_Y SCREEN_Y
#define STATUSBAR_W SCREEN_W
#define STATUSBAR_H 80
#define WINDOW_X SCREEN_X
#define WINDOW_Y SCREEN_Y+STATUSBAR_H
#define WINDOW_W SCREEN_W
#define WINDOW_H SCREEN_H-STATUSBAR_H

#endif // _HACHELP_H_
