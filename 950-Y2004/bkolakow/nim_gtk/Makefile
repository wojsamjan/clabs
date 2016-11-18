# Jakub S³awiñski 13.12.2003 r.
# Makefile do programu graj±cego w warcaby

CC=gcc
gtkl=$(shell pkg-config --cflags --libs gtk+-2.0)
gtklf=$(shell pkg-config --cflags gtk+-2.0)
cflags= -Wall -O2 
CFLAGS= $(cflags) $(gtkl)
PROGRAMS= program

all: $(PROGRAMS)

program: main.o funkcje.o nim.o minimax.o main.h nim.h minimax.h
	$(CC) $(CFLAGS) main.o funkcje.o nim.o minimax.o -o program

main.o: main.c main.h nim.h minimax.h
	$(CC) $(cflags) $(gtklf) -c main.c

funkcje.o: funkcje.c main.h nim.h minimax.h
	$(CC) $(cflags) $(gtklf) -c funkcje.c

nim.o: nim.c main.h nim.h minimax.h
	$(CC) $(cflags) $(gtklf) -c nim.c

minimax.o: minimax.c main.h nim.h minimax.h
	$(CC) $(cflags) $(gtklf) -c minimax.c

.PHONY: clean progs

clean:
	rm -rf *.o *~
progs:
	rm -rf $(PROGRAMS)
