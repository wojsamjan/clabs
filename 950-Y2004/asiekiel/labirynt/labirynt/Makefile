#
# JP1                                                           1.X.2003
#
# Labirynty

CC = gccx
CFLAGS = -Wall -g

maze = mazelib.h mazelib.c
csources = maze.c

programs = $(csources:.c=)

.PHONY : clean 

maze : maze.o mazelib.o

mazelib.o : mazelib.c mazelib.h

maze.o : maze.c mazelib.h


clean:
	rm -f core \#* *~ *.o $(programs)
