#
#  $URL: http://manta.univ.gda.pl/svn/wb/labs/c/535-Zbiory/Makefile $
#  $Revision: 217 $

CFLAGS = -Wall -std=c99
#LDFLAGS = -lcii
LOADLIBES = -lcii

all: test_set xref

clean: 
	rm -f \#* *~ a.out *~ *.o test_set do_test xref sfree


test_set.o : test_set.c getword.h

test_set : test_set.o getword.o
	cc $(CFLAGS) -o $@ $^ -lcii

getword.o : getword.c getword.h

xref.o : getword.o getword.h xref.c

xref : xref.o getword.o
	cc $(CFLAGS) -o $@ $^ -lcii

# --- uzupełnić kod w do_set.c

do_test.o : do_test.c getword.h

do_test : do_test.o getword.o
	cc $(CFLAGS) -o $@ $^ -lcii
