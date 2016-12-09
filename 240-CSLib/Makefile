sources := $(shell ls -1 *.c)
programs = $(sources:.c=)
# programs = $(basename $(sources))

CFLAGS = -std=c11 -Wall
CC = gccx

all : $(programs)

.PHONY : clean

clean :
	rm -f core *.o *~ a.out $(programs)
	rm -rf *.dSYM
