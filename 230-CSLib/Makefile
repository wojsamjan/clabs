programs = randtest cointest dicetest dicetest2 craps 

CC = gccx
CFLAGS = -Wall

all : $(programs)

.PHONY : clean

clean :
	rm -f core *~ \#* *.o $(programs)

randtest.o : randtest.c
	$(CC) $(CFLAGS) -c randtest.c

cointest.o : cointest.c
	$(CC) $(CFLAGS) -c cointest.c

dicetest.o : dicetest.c
	$(CC) $(CFLAGS) -c dicetest.c

dicetest2.o : dicetest2.c
	$(CC) $(CFLAGS) -c dicetest2.c

craps.o : craps.c
	$(CC) $(CFLAGS) -c craps.c

randtest : randtest.o
	$(CC) $(CFLAGS) -o randtest randtest.o

cointest : cointest.o
	$(CC) $(CFLAGS) -o cointest cointest.o

dicetest : dicetest.o
	$(CC) $(CFLAGS) -o dicetest dicetest.o

craps : craps.o
	$(CC) $(CFLAGS) -o craps craps.o
