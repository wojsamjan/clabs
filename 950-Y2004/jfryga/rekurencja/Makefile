#
# JP2                                                           1.X.2003
#
#
# Pliki nc-hanoi.c test_priv.h zostaly skopiowane z pakietu ncurses-devel

CC = gccx
FLAGS= -Wall -g
LDFLAGS = -lcurses

exercises = telefon.c binarycode.c graycode.c subsets.c
csources = $(exercises)

programs = $(csources:.c=)

.PHONY : clean 

all : $(programs)

clean:
	rm -f core \#* *~ *.o $(programs)
