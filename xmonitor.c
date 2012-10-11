#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <errno.h>
#include "xmonitor.h"
#include "events.h"
#include "log.h"

static XEvent event;
static Display *dis;
static Window   root;
static int 	screen = -1;
static XRROutputInfo *output_info;
static XRRScreenResources *res;

void insert_event(const XRRNotifyEvent *e, const struct timeval *t){
	int i;
	char msg[255];
	t_event ev;
	ev.etype = e->type;

	memcpy(&ev.timestamp, t, sizeof (struct timeval));

	/*if (exec_count == 0){
		exec_events[0] = ev;
		exec_count++;
	}else if(exec_count == NUM_EVENTS){
		logMessage(INFO, "Executed events cache full, discarding oldest one\n");
		exec_events[0] = ev;
	}else{
		exec_events[exec_count - 1] = ev;
		exec_count++;
	}	


	sprintf(msg, "Event cache size: %d\n ================== \n", exec_count);
	logMessage(INFO, msg);
	for (i = 0; i <= exec_count ; i++){
		sprintf(msg, "Position: %d, event type: %d, timestamp: %d\n", i, exec_events[i].etype, exec_events[i].timestamp);
		logMessage(INFO, msg);
	}*/

	if (exec_count == 0){
		exec_events[0] = ev;
		exec_count++;
		cache_pos++;

		logMessage(INFO, "Starting executed event cache\n");
	}else if (exec_count <= NUM_EVENTS){
		exec_events[exec_count - 1] = ev;
		exec_count++;
		cache_pos++;

		sprintf(msg, "Added %d into events cache, now size is: %d\n", ev.etype, exec_count);
		logMessage(INFO, msg);		
	}else{
		exec_events[(cache_pos % NUM_EVENTS) - 1] = ev;
		cache_pos++;

		logMessage(INFO, "Events cache full, replacing oldest one\n");
	}

	sprintf(msg, "cache count: %d =============\n", exec_count);
	logMessage(INFO, msg);
	for (i = 0; i < NUM_EVENTS; i++){
		sprintf(msg, "\tCache[%d]} = Event: %d, timestamp: %ld %ld\n", i, exec_events[i].etype, exec_events[i].timestamp.tv_sec, exec_events[i].timestamp.tv_usec);
		logMessage(INFO, msg);
	}

	logMessage(INFO, "Event cache dump end =========================\n");

}

int check_event(const XRRNotifyEvent *e, const struct timeval *t){
	int i;
	char *msg = (char*)malloc(255 * sizeof(char));
	for (i = 0; i <= exec_count ; i++){
		if(exec_events[i].etype == e->type){
			time_t tsdiff = t->tv_sec - exec_events[i].timestamp.tv_sec;
			time_t tusdiff = 0;
			time_t tdiff;
			
			if (tsdiff == 0){
				tusdiff = t->tv_usec - exec_events[i].timestamp.tv_usec;
			}

			tdiff = tsdiff + (100 * tusdiff);

			/*printf("t: %d, old t: %d\n", t, exec_events[i].timestamp);*/
			sprintf(msg, "Event already found, time diff %lu. (> THS? %d)\n", tdiff, tdiff >= TIME_THS);
			logMessage(INFO, msg);
			return tdiff >= TIME_THS ? 1 : 0;
		}
	}

	return 1;
}

int init_monitor(){
	int outi;
	char msg[255];
	dis = XOpenDisplay(NULL);

	startLogger();

	if (!dis){
		logMessage(ERROR, "Cannot connect into XServer using default display...exiting");
		return ENOMEM;
	}

	screen = DefaultScreen(dis);

	logMessage(INFO, "Loading root window");
	root = RootWindow(dis, screen);

	/*Select X input to handle the events*/
	logMessage(INFO, "Selecting input");
	XSelectInput(dis, root, StructureNotifyMask);

	/*Getting Screen Resources*/
	logMessage(INFO, "Getting screen resources");
	res = XRRGetScreenResources(dis, root);

	sprintf(msg, "%d resources found", res->noutput);
	
	logMessage(INFO, msg);

	for (outi = 0; outi < res->noutput; outi++){
		output_info = XRRGetOutputInfo(dis, res, res->outputs[outi]);
	
		sprintf(msg, "Output name: %s", output_info->name);
		
		logMessage(INFO, msg);
	}

	return 0;
}

void start_monitor(){
	struct timeval *currenttime;
	exec_count = 0;

	currenttime = (struct timeval*)malloc(sizeof(struct timeval));

	exec_events = (t_event*)calloc(NUM_EVENTS, sizeof(t_event));

	/*Keep waiting for new X events for a given screen*/
	while(1){
		XNextEvent(dis, (XEvent*) &event);

		XRRNotifyEvent *ev = (XRRNotifyEvent*)&event;

		gettimeofday(currenttime, NULL);

		if(!check_event(ev, currenttime)){
			logMessage(WARNING, "Event already executed within threshold parameters..skiping this round\n");
			continue;
		}

		insert_event(ev, currenttime);
		
		execute_events(&event);
	}

	free(currenttime);
	free(exec_events);
}

int main(int argc, char **argv){
	int init_status;

	if((init_status = init_monitor())){
		fprintf(stderr, "Xevent-monitor failed to init, aborting...\n");
		return init_status;
	}

	start_monitor();

	endLogger();

	return EXIT_SUCCESS;
}
