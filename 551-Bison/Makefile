
#  $URL: http://manta.univ.gda.pl/svn/wb/labs/c/551-Bison/Makefile $
#  $Revision: 89 $
#  $Date: 2006-01-03 13:40:00 +0100 (wto, 03 sty 2006) $


.PHONY : all clean propset

CFLAGS = -Wall -ggdb -ansi


calc0 : calc0.y
	bison calc0.y
	cc calc0.tab.c -o calc0

calc1 : calc1.y
	bison calc1.y
	cc calc1.tab.c -o calc1


propset :
	svn propset svn:keywords "Revision Date URL Author" *

clean :
	rm -f *~ *.o *.ps a.out ex1.output *.tab.c calc0 calc1


