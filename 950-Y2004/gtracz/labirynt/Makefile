#
# JP1                                                           1.X.2003
#
# Labirynty

CC = gcc
CFLAGS = -Wall -g -I/usr/include/ncurses

maze = mazelib.h mazelib.c -lncurses
csources = maze.c

programs = $(csources:.c=)

.PHONY : clean 

maze : maze.c mazelib.c -lncurses

#
#mazelib.o : mazelib.c mazelib.h
#
#maze.o : maze.c mazelib.h
#

clean:
	rm -f core \#* *~ *.o $(programs)
