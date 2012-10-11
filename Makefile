CC	= gcc
CFLAGS	= -Wall -O2 -g
LD	= gcc
LDFLAGS	=
LIBS	= `pkg-config --libs x11 xrandr`
OBJS	= events.o xmonitor.o log.o

.c.o:
	$(CC) -c $(CFLAGS) -o $*.o $<

all: xevent-monitor

xevent-monitor: $(OBJS)
	$(LD) -o $@ $(LDFLAGS) $(OBJS) $(LIBS)

events: events.h log.h

xmonitor: xmonitor.h log.h

log: log.h

clean:
	rm -f xevent-monitor $(OBJS)

