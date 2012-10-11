#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include "events.h"
#include "log.h"


int execute_events(XEvent *e){
	/*Getting event subtype code, wich is used to get the events dir*/
	/*int etype = ((XRRNotifyEvent*)e)->subtype;*/
	int etype = e->type;
	char dir[128];
	char msg[255];
	struct dirent *f;
		
	sprintf(dir, "%s/%d", EVENTS_PATH, etype);

	DIR *d = opendir(dir);

	sprintf(msg, "Checking dir %s for any scripts\n", dir);

	logMessage(INFO, msg);

	if (!d){
		sprintf(msg, "Could not find configuration dir for event: %d", etype);
		logMessage(WARNING, msg);

		switch(errno){
			case EACCES:
				logMessage(ERROR, " permission denied");
			break;
			case ENOENT:
				logMessage(ERROR, " dir not found");
			break;
			default:
				logMessage(ERROR, " unkown error");
			break;
		}

		return 0;
	}
	
	while((f = readdir(d)) != NULL){
		char *name = (char*)malloc(128 * sizeof(char*));;

		sprintf(name, "%s/%d/%s", EVENTS_PATH, etype, f->d_name);
	
		if (strcmp(f->d_name, ".") == 0 || strcmp(f->d_name, "..") == 0)
			continue;
	
		if (fork() == 0){
			sprintf(msg, "Executing %s for event %d\n", name, etype);
			logMessage(INFO, msg);
			if (execl(name, name, NULL) == -1){
				sprintf(msg, "Error on executing %s for event %d, error code: %d\n", name, etype, errno);
				logMessage(ERROR, msg);
			}
		}else{
			int status;
			wait(&status);
			continue;
		}
	}

	return 1;
}
