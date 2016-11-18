CC = cc
CFLAGS = -Wall -ggdb -pedantic -ansi -lncurses

maze = mazelib.h mazelib.c
csources = maze.c

programs = $(csources:.c=)

.PHONY : clean 

#maze : main.o mazelib.o

#mazelib.o : mazelib.c mazelib.h

#maze.o : main.c mazelib.h

all:
	gccx $(CFLAGS) maze.c mazelib.c -o maze

clean:
	rm -f core \#* *~ *.o $(programs)
