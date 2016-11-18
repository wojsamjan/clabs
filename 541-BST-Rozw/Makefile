
#  $Revision: 61 $
#  $Date: 2005-11-22 00:05:29 +0100 (wto, 22 lis 2005) $
#  $URL: http://manta.univ.gda.pl/svn/wb/labs/c/541-BST-Rozw/Makefile $

#  svn propset svn:keywords "Revision Date URL Author" *

CFLAGS = -Wall -ggdb

examples = hasPathSum.c printPaths.c mirror.c sameTree.c isBST.c
programs = $(examples:.c=)


all : $(programs)


BT.o : BT.c BT.h

tree01.o : tree01.c BT.h

tree02.o : tree02.c BT.h

tree03.o : tree03.c BT.h

tree04.o : tree04.c BT.h


hasPathSum.o : hasPathSum.c BT.h

hasPathSum : hasPathSum.o BT.o tree01.o
	$(CC) $^ -o $@


printPaths.o : printPaths.c BT.h

printPaths : printPaths.o BT.o tree02.o
	$(CC) $^ -o $@


mirror.o : mirror.c BT.h

mirror : mirror.o BT.o tree03.o
	$(CC) $^ -o $@


sameTree.o : sameTree.c BT.h

sameTree : sameTree.o BT.o tree03.o
	$(CC) $^ -o $@


isBST.o : isBST.c BT.h

isBST : isBST.o BT.o tree04.o
	$(CC) $^ -o $@


%.ps : %.h
	enscript --font QuasiCourier@10 -GE -p$@ $^

%.ps : %.c
	enscript --font QuasiCourier@10 -GE -p$@ $^


clean :
	rm -f *~ \#* core *.o *.{ps,ljet4} $(programs)


programs.ps: $(examples)
	enscript -v --font QuasiCourier@10 -GE -p$@ $^
#	enscript -Xlatin2 -G2rE -U2 -p$@ $< 

programs.ljet4 : programs.ps
	gs -dNOPAUSE -dBATCH -sDEVICE=ljet4d -sOutputFile=programs.ljet4 $<
