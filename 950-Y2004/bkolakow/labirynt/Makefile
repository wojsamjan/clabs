main: main.o funkcje.o
	cc main.o funkcje.o -lncurses -g -o maze

main.o: main.c main.h
	cc -c main.c

funkcje.o: funkcje.c
	cc -c funkcje.c

.PHONY: clean

clean: 
	rm -f *~ *.o out
