#include <stdlib.h>
#include <stdio.h>

#define OUT_LOG "/var/log/xmonitor.log"
#define ERR_LOG "/var/log/xmonitor_error.log"

/*Defines the log messages level*/
typedef enum t_loglevel{
	ERROR = 2,
	WARNING = 1,
       	INFO = 0	
}t_loglevel;

/*Starts logger module*/
void startLogger();

/*Logs a message into log file*/
void logMessage(t_loglevel, char *);

/*Ends log module*/
void endLogger();
