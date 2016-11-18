#
# JP1                                                           1.X.2003
#
# Labirynty

CC = gccx
CFLAGS = -Wall -g
LDFLAGS= -lncurses

maze = mazelib.h mazelib.c cmaze.h cmaze.c 
csources = maze.c

programs = $(csources:.c=)

.PHONY : clean 

maze : maze.o mazelib.o cmaze.o

mazelib.o : mazelib.c mazelib.h

maze.o : maze.c mazelib.h

cmaze.o: cmaze.c mazelib.h
 
clean:
	rm -f core \#* *~ *.o $(programs)
