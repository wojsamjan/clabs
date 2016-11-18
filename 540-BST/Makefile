
# $Revision: 59 $
# $URL: http://manta.univ.gda.pl/svn/wb/labs/c/540-BST/Makefile $

CFLAGS = -Wall -ggdb

h_sources = build123.h BT.h
c_sources = build123.c 
examples = main.c maxDepth.c minValue.c 

programs = $(examples:.c=)

all : $(programs)


BT.o : BT.c BT.h

build123.o : build123.c build123.h BT.h

main.o : main.c build123.h

main : main.o build123.o BT.o
	$(CC) $^ -o $@


# zadania

maxDepth.o : maxDepth.c BT.h

maxDepth : maxDepth.o BT.o
	$(CC) $^ -o $@


minValue.o : minValue.c BT.h

minValue : minValue.o BT.o
	$(CC) $^ -o $@



clean :
	rm -f *~ \#* core *.o programs.{ps,ljet4} $(programs)


programs.ps: $(h_sources) $(c_sources)
	enscript -GE -p$@ $^
#	enscript -Xlatin2 -G2rE -U2 -p$@ $< 

programs.ljet4 : programs.ps
	gs -dNOPAUSE -dBATCH -sDEVICE=ljet4 -sOutputFile=programs.ljet4 $<
