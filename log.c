#include <sys/types.h>
#include <errno.h>
#include "log.h"

/*Log gile FD*/
static FILE *logfile;
static FILE *errorfile;

/*Log level to string mapping*/
static char *levelMap[3];


void startLogger(){
	levelMap[0] = "INFO";
	levelMap[1] = "WARNING";
	levelMap[2] = "ERROR";

	logfile = fopen(OUT_LOG, "w+");
	errorfile = fopen(ERR_LOG, "w+");

	if (!logfile || !errorfile){
		fprintf(stdout, "Could not start logfiles, XEvent-Monitor daemon initialize failed..\n");

		exit(errno);
	}
}

void logMessage(t_loglevel l, char *m){
	if (l == ERROR){
		fprintf(errorfile, "[%s] %s\n", levelMap[l], m);
	}else{
		fprintf(logfile, "[%s] %s\n", levelMap[l], m);
	}

	fflush(errorfile);
	fflush(logfile);

	printf("[%s] %s\n", levelMap[l], m);
}

void endLogger(){
	fclose(logfile);
	fclose(errorfile);
}
