CC = cc
CFLAGS = -Wall -ggdb -pedantic -ansi -lncurses

#maze = mazelib.h mazelib.c
csources = main.c

programs = $(csources:.c=)

.PHONY : clean 

#maze : main.o mazelib.o

#mazelib.o : mazelib.c mazelib.h

#maze.o : main.c mazelib.h

all:
	gccx $(CFLAGS) main.c connect.c ui-connect.c minimax.c -o con

clean:
	rm -f core \#* *~ *.o $(programs)
