############################################################

CC = gccx
CFLAGS = -g -Wall -pedantic -ansi
LDFLAGS = -lcurses

############################################################

exercises = binarycode.c graycode.c subsets.c partitions.c telefon.c permutacje3.c
csources = $(exercises)
programs = $(csources:.c=)

############################################################

all : $(programs)

############################################################

.PHONY : clean tidy


clean:
	rm -f core \#* *~ *.o $(programs)
tidy:
	rm -f core \#* *~ *.o

############################################################
############################################################
