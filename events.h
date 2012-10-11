#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <dirent.h>

#define EVENTS_PATH "/etc/xevent-monitor/events.d"

/*Execute scripts for a given XEvent code*/
int execute_events(XEvent*);
