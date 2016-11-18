CC = gcc
GTK_CFLAGS := $(shell pkg-config --cflags gtk+-2.0)
GTK_LDFLAGS := $(shell pkg-config --libs gtk+-2.0)
CFLAGS = -Wall -g -D_GNU_SOURCE $(GTK_CFLAGS) -fno-inline-functions

programs = labirynt

all : $(programs)

gtk.o : gtk.c gui.h

menu.o :  menu.c

mazelib.o : mazelib.c

maze_gen.o : maze_gen.c

labirynt : gtk.o maze_gen.o menu.o mazelib.o
	$(CC) -o $@ $^ $(GTK_LDFLAGS)
	$(RM) -f \#* *~ *.o

.PHONY : clean 

clean:
	$(RM) -f core \#* *~ *.o $(programs)
