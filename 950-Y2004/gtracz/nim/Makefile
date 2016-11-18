#
# JP2                                                           1.X.2003
#
#
# Przyk³adowy plik Makefile do NIM.

CC = gcc
CFLAGS = -Wall -g -I/usr/include/ncurses


program = nim

nim : main.c nim.c minimax.c -lncurses

.PHONY : clean 

clean:
	rm -f core \#* *~ *.o $(program)
