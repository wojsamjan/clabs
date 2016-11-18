CC = gccx
CFLAGS = -Wall -g
LDFLAGS = -lcurses

exercises = binarycode.c partitions.c
csources = $(exercises)

programs = $(csources:.c=)

.PHONY : clean 

all : $(programs)

clean:
	rm -f core \#* *~ *.o $(programs)
