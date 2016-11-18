# Jakub S³awiñski 13.12.2003 r.
# Makefile do programu graj±cego w warcaby

CC=gcc
gtkl=$(shell pkg-config --cflags --libs gtk+-2.0)
gtklf=$(shell pkg-config --cflags gtk+-2.0)
cflags= -Wall -O2 
CFLAGS= $(cflags) $(gtkl)
PROGRAMS= draughts

all: $(PROGRAMS)

draughts: draughts.c draugfun.o dragraph.o dramm.o nodes.o
	$(CC) $(CFLAGS) draughts.c draugfun.o dragraph.o dramm.o nodes.o -o draughts

draugfun.o: draugfun.c draughts.h
	$(CC) $(cflags) $(gtklf) -c draugfun.c

dragraph.o: dragraph.c dragraph.h
	$(CC) $(cflags) $(gtklf) -c dragraph.c

dramm.o: dramm.c dramm.h
	$(CC) $(cflags) $(gtklf) -c dramm.c

nodes.o: nodes.c 
	$(CC) $(cflags) -c nodes.c

.PHONY: clean

clean:
	rm -rf *.o *~ $(PROGRAMS)
