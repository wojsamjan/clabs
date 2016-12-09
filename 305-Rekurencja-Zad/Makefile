# Pliki nc-hanoi.c test_priv.h zostaly skopiowane z pakietu ncurses-devel

CC = gccx
CFLAGS = -Wall -std=c11
LDFLAGS = -lcurses

examples =  nc-hanoi.c hanoi.c permutacje.c permutacje2.c
exercises = permutacje3.c telefon.c subsets.c binarycode.c graycode.c partitions.c
# csources = $(examples) $(exercises)
# programs = $(csources:.c=)

programs = $(examples:.c=)

.PHONY : clean

all : $(programs)

clean:
	rm -f core \#* *~ *.o *.ps $(programs)
