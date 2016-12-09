sources = README Makefile oddeven.c euclid.c
programs = oddeven euclid

# cs-includes = /usr/local/include/cslib
# cs-library = /usr/local/lib/cslib.a

# CFLAGS = -std=c11 -Wall -I. -I$(cs-includes)
# LDLIBS =  $(cs-library)

CFLAGS = -std=c11 -Wall -pedantic
CC = gccx

all : oddeven euclid

.PHONY : clean

clean :
	rm -f core *.o *~ *.ps a.out $(programs)
	rm -rf *.dSYM
