
CC = gccx
CFLAGS = -Wall -ansi -pedantic

piglatin: main.o piglatin.o
	cd ../scanner ; $(MAKE)
	$(CC) $(CFLAGS) -o piglatin main.o piglatin.o ../scanner/scanner.o

piglatin.o: piglatin.c piglatin.h
	$(CC) $(CFLAGS) -c piglatin.c

main.o: main.c ../scanner/scanner.h piglatin.h
	$(CC) $(CFLAGS) -I../scanner -c main.c

clean:
	rm -f *~ core a.out
	rm -f *.o piglatin
