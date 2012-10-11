#include <sys/time.h>

#define NUM_EVENTS 5
#define TIME_THS 3

typedef unsigned int UINT;

/*Struct used to store execution time for each event*/
typedef struct t_event{
	UINT etype;
	struct timeval timestamp;
}t_event;

t_event *exec_events;

int exec_count = 0;

int cache_pos = 0;

void start_monitor();

int init_monitor();

/*Check if event were executed within NUM_EVENTS && TIME_THS before
 * returns 1 wether not or 0 in case it was
 */
int check_event(const XRRNotifyEvent *, const struct timeval*);

void insert_event(const XRRNotifyEvent *, const struct timeval*);
