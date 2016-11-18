#
# JP2                                                           1.X.2003
#
# Rozwi±zania zadañ z 11-Hanoi. 

CC = gccx
CFLAGS = -Wall -g

csources = permutacje3.c telefon.c subsets.c binarycode.c graycode.c partitions.c

programs = $(csources:.c=)

.PHONY : clean 

all : $(programs)

clean:
	rm -f core \#* *~ *.o $(programs)
