# 
#   $URL: http://manta.univ.gda.pl/svn/wb/labs/c/515-LL3/Makefile $
#   $Revision: 110 $
#

help :
	@echo Ścieżki do CII: /usr/local/{lib,include/cii}

CLIBS = -lcii

headers = list.h atom.h
sources = test1.c test2.c test3.c

programs = $(sources:%.c=%) 

all : test1 test2 test3

test1 : test1.o
	cc $< -o $@ -lcii
test2 : test2.o
	cc $< -o $@ -lcii
test3 : test3.o
	cc $< -o $@ -lcii

.PHONY : clean

all.ps : $(headers) $(sources)
	enscript -f PLTypewriter10-Regular@12 -X latin2 -GE -p$@ $^
#	enscript -v -f Courier@12 -X latin2 -GE -p$@ $^

clean :
	rm -f *~ \#* *.o *.ps $(programs)
