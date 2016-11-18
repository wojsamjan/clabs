#
# JP2                                                           1.X.2003
#
#
# Gra ,,NIM''

CC = gccx
CFLAGS = -Wall -g

csources = main.c nim.c
headers = nim.h

programs = nim

all : $(programs)

main.o : main.c nim.h

nim.o : nim.c nim.h

nim : main.o nim.o
	$(CC) -o $@ $^

.PHONY : clean 

clean:
	rm -f core \#* *~ *.o $(programs)
