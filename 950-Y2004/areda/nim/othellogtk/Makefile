# Gra "Othello"

#all: $(objects)
#	gcc -o othellogtk $(objects) $(GTK_LDFLAGS)
#
#clean:
#	$(RM) othellogtk $(objects) *~ core


CC = gcc
GTK_CFLAGS := $(shell pkg-config --cflags gtk+-2.0)
GTK_LDFLAGS := $(shell pkg-config --libs gtk+-2.0)
CFLAGS = -Wall -g -D_GNU_SOURCE $(GTK_CFLAGS) -O3 -finline-functions

csources = main.c othello.c minimax.c othello_gtk.c menu.c
headers = othello.h minimax.h othello_gtk.h menu.h

programs = othellogtk

all : $(programs)

main.o : main.c othello.h main.h

othello.o : othello.c othello.h 

minimax.o : minimax.c minimax.h othello.h

othello_gtk.o : othello_gtk.c

menu.o :  menu.c

othellogtk : main.o othello.o minimax.o othello_gtk.o menu.o
	$(CC) -o $@ $^ $(GTK_LDFLAGS) 

.PHONY : clean 

clean:
	$(RM) -f core \#* *~ *.o $(programs)
