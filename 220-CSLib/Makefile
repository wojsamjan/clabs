
sources = README Makefile oddeven.c euclid.c
programs = oddeven euclid

#cs-includes = /usr/local/include/cslib
#cs-library = /usr/local/lib/cslib.a

#CFLAGS =  -ansi -Wall -g -pedantic -I. -I$(cs-includes)
CFLAGS =  -ansi -Wall -g -pedantic
#LDLIBS =  $(cs-library)
CC = gccx

all : oddeven euclid

#GetInteger.o : GetInteger.c
#	$(CC) -c GetInteger.c

oddeven.o : oddeven.c
	$(CC) -c oddeven.c

#oddeven : oddeven.o GetInteger.o
#	$(CC) -o oddeven oddeven.o GetInteger.o $(cs-library)
#	$(CC) -o oddeven oddeven.o GetInteger.o

programs.ps : $(sources) Makefile
#	enscript --encoding=latin2 -G2rE -U2 -p$@ $^
	enscript --encoding=latin2 -GE -p$@ $^

.PHONY : clean

clean :
	rm -f core *.o *~ *.ps $(programs)
