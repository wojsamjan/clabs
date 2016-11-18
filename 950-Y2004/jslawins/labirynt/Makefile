# Jakub S³awiñski (Slaughter House Entertainment Group)
# Makefile do mw_maze oraz maze
# Makefile

CC = gcc
CFLAGS = -Wall -pedantic -O2

programs = maze mw_maze
zalezne = mw_maze.o grafika.o myfunkc.o stany.o mw_lib.o siec.o mw_serw.o mw_klie.o

all: info1 maze ok info2 mw_maze
	@echo "  >>>OK!"

info1:
	@echo -e "\nKompilacja maze - wersja podstawowa\n"

info2: 
	@echo -e "\nKompilacja maze walkera - wersja 0.2b - grafika: ncurses\n"

ok:
	@echo "  >>>OK!"


#mw_maze

mw_maze: mw_main.c $(zalezne)
	$(CC) $(CFLAGS) -lncurses -lpthread mw_main.c $(zalezne) -o mw_maze
	
# maze

maze: maze.o mazelib.o
	$(CC) $(CFLAGS) maze.o mazelib.o -o maze

maze.o: maze.c mazelib.h
	$(CC) $(CFLAGS) -c maze.c

mazelib.o: mazelib.c mazelib.h
	$(CC) $(CFLAGS) -c mazelib.c

# mw_maze

mw_maze.o: mw_maze.c mw_maze.h
	$(CC) $(CFLAGS) -c mw_maze.c

grafika.o: grafika.c grafika.h
	$(CC) $(CFLAGS) -c grafika.c

myfunkc.o: myfunkc.c myfunkc.h
	$(CC) $(CFLAGS) -c myfunkc.c

stany.o: stany.c stany.h
	$(CC) $(CFLAGS) -c stany.c

mw_lib.o: mw_lib.c mw_lib.h
	$(CC) $(CFLAGS) -c mw_lib.c

siec.o: siec.c siec.h
	$(CC) $(CFLAGS) -c siec.c

mw_serw.o: mw_serw.c mw_serw.h
	$(CC) $(CFLAGS) -c mw_serw.c

mw_klie.o: mw_klie.c mw_klie.h
	$(CC) $(CFLAGS) -c mw_klie.c

# clean

.PHONY: clean

clean:
	rm -f core \#* *~ *.o $(programs)
