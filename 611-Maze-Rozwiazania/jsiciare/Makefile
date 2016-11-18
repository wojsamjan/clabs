PROGRAM = maze
CC	= gcc
CFLAGS	= -Wall -pedantic -ansi -I/usr/include/ncurses
CLIBS	= -lcurses

all : smartxl


# NIE WIDZI DRZWI WYJ¦CIOWYCH:

s : clean
	$(CC) $(CFLAGS) $(CLIBS) -DSIZE=0 -o$(PROGRAM) $(PROGRAM).c
	./$(PROGRAM)

m : clean
	$(CC) $(CFLAGS) $(CLIBS) -DSIZE=1 -o$(PROGRAM) $(PROGRAM).c
	./$(PROGRAM)

l : clean
	$(CC) $(CFLAGS) $(CLIBS) -DSIZE=2 -o$(PROGRAM) $(PROGRAM).c
	./$(PROGRAM)

xl : clean
	$(CC) $(CFLAGS) $(CLIBS) -DSIZE=3 -o$(PROGRAM) $(PROGRAM).c
	./$(PROGRAM)



# WIDZI DRZWI WYJ¦CIOWE:

smarts : clean
	$(CC) $(CFLAGS) $(CLIBS) -DSMART -DSIZE=0 -o$(PROGRAM) $(PROGRAM).c
	./$(PROGRAM)

smartm : clean
	$(CC) $(CFLAGS) $(CLIBS) -DSMART -DSIZE=1 -o$(PROGRAM) $(PROGRAM).c
	./$(PROGRAM)

smartl : clean
	$(CC) $(CFLAGS) $(CLIBS) -DSMART -DSIZE=2 -o$(PROGRAM) $(PROGRAM).c
	./$(PROGRAM)

smartxl : clean
	$(CC) $(CFLAGS) $(CLIBS) -DSMART -DSIZE=3 -o$(PROGRAM) $(PROGRAM).c
	./$(PROGRAM)



######################################################

.PHONY : clean

clean :
	@rm -f *~ \#* *.o a.out core $(PROGRAM)
