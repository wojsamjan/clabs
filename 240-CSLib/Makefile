
PROGRAMS = \
    acronym \
    addlist \
    lastchar \
    linelen \
    ncopies \
    protect \
    reverse \
    secondh \
    repfirst 

CC = gccx
CFLAGS = -Wall -ansi -pedantic

all: $(PROGRAMS)

clean:
	rm -f ,* .,* *~ core a.out graphics.ps
	rm -f *.o *.a $(PROGRAMS)

# --------------------------------------------

acronym.o: acronym.c
	$(CC) $(CFLAGS) -c acronym.c

addlist.o: addlist.c
	$(CC) $(CFLAGS) -c addlist.c

lastchar.o: lastchar.c
	$(CC) $(CFLAGS) -c lastchar.c

linelen.o: linelen.c
	$(CC) $(CFLAGS) -c linelen.c

ncopies.o: ncopies.c
	$(CC) $(CFLAGS) -c ncopies.c

protect.o: protect.c
	$(CC) $(CFLAGS) -c protect.c

reverse.o: reverse.c
	$(CC) $(CFLAGS) -c reverse.c

secondh.o: secondh.c
	$(CC) $(CFLAGS) -c secondh.c

repfirst.o: repfirst.c
	$(CC) $(CFLAGS) -c repfirst.c


acronym: acronym.o
	$(CC) $(CFLAGS) -o acronym acronym.o

addlist: addlist.o
	$(CC) $(CFLAGS) -o addlist addlist.o

lastchar: lastchar.o
	$(CC) $(CFLAGS) -o lastchar lastchar.o

linelen: linelen.o
	$(CC) $(CFLAGS) -o linelen linelen.o

ncopies: ncopies.o
	$(CC) $(CFLAGS) -o ncopies ncopies.o

protect: protect.o
	$(CC) $(CFLAGS) -o protect protect.o

reverse: reverse.o
	$(CC) $(CFLAGS) -o reverse reverse.o

secondh: secondh.o
	$(CC) $(CFLAGS) -o secondh secondh.o

repfirst: repfirst.o
	$(CC) $(CFLAGS) -o repfirst repfirst.o
