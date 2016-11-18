#
# JP2                                                           1.X.2003
#
#
# Przyk³adowy plik Makefile do NIM.

CC = gcc
CFLAGS = -Wall -g

csources = main.c nim.c minimax.c
headers = nim.h minimax.h

program = nim

all : $(program)

main.o : main.c nim.h minimax.h

nim.o : nim.c nim.h

minimax.o : minimax.c minimax.h nim.h

nim : main.o nim.o minimax.o
	$(CC) -lncurses -o $@ $^

.PHONY : clean 

clean:
	rm -f core \#* *~ *.o $(program)
