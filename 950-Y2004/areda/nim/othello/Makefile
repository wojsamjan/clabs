# Gra "Othello"

CC = gccx
CFLAGS = -Wall -g -fwritable-strings

csources = main.c othello.c ui-othello.c minimax.c
headers = othello.h ui-othello.h minimax.h

programs = othello

all : $(programs)

main.o : main.c othello.h

othello.o : othello.c othello.h ui-othello.h

ui-othello.o : ui-othello.c ui-othello.h othello.h

minimax.o : minimax.c minimax.h othello.h

othello : main.o othello.o ui-othello.o minimax.o
	$(CC) -o $@ $^

.PHONY : clean 

clean:
	rm -f core \#* *~ *.o $(programs)
