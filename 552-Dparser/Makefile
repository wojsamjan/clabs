#
# $URL: http://manta.univ.gda.pl/svn/wb/labs/c/552-Dparser/Makefile $
# $Revision: 90 $
#

CFLAGS = -Wall -ggdb -I/usr/local/include
LIBS =  -L/usr/local/lib -ldparse

%.g.d_parser.c : %.g
	make_dparser $^

#%.g.d_parser.o : %.g.d_parser.c

icalc : icalc.g.d_parser.o driver.o
#	make_dparser icalc.g
	$(CC) -o icalc driver.o icalc.g.d_parser.o -I/usr/local/include -L/usr/local/lib -ldparse

rcalc1 : rcalc1.g.d_parser.o driver.o
	$(CC) -o rcalc1 driver.o rcalc1.g.d_parser.o -I/usr/local/include -L/usr/local/lib -ldparse

rcalc2 : rcalc2.g.d_parser.o driver.o
	$(CC) -o rcalc2 driver.o rcalc2.g.d_parser.o -I/usr/local/include -L/usr/local/lib -ldparse



.PHONY : clean propset

clean :
	rm -f icalc rcalc[12]
	rm -f \#* *~ *.o *.d_parser.c

propset :
	svn propset svn:keywords "URL Revision Author" Makefile *.g driver.c
