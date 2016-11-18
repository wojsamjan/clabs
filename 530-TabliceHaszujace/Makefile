#
#  $URL: http://manta.univ.gda.pl/svn/wb/labs/c/530-TabliceHaszujace/Makefile $
#  $Revision: 172 $

CFLAGS = -Wall -ansi
#LDFLAGS
#LOADLIBES

getword.o : getword.c getword.h

wf.o : getword.o getword.h wf.c

test_getword.o : test_getword.c getword.h

wf : wf.o getword.o
	cc $(CFLAGS) -o $@ $^ -lcii

test_getword : test_getword.o getword.o
	cc $(CFLAGS) -o $@ $^ -lcii

all: wf

clean: 
	rm -f *~ a.out *~ *.o wf test_getword
