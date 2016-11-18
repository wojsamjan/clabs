
#  $URL: http://manta.univ.gda.pl/svn/wb/labs/c/550-ParsingElementarz/Makefile $
#  $Revision: 183 $
#  $Date: 2006-11-19 16:29:41 +0100 (nie, 19 lis 2006) $


.PHONY : all clean propset

CFLAGS = -Wall -ggdb -ansi

error.o : error.c error.h

main.o : main.c parser.h backend.h error.h

lex.o : lex.c lex.h

flex.c : flex.l
	flex -oflex.c flex.l

flex.o : flex.c lex.h
	$(CC) -c flex.c

parser.o : parser.c parser.h lex.h error.h

code_gen.o : code_gen.c parser.h backend.h

interpret.o : interpret.c parser.h backend.h


code_gen : main.o lex.o parser.o error.o code_gen.o
	$(CC) -o $@ $^

interpret : main.o lex.o parser.o error.o interpret.o
	$(CC) -o $@ $^

finterpret : main.o flex.o parser.o error.o interpret.o
	$(CC) -o $@ $^ -lfl



propset :
	svn propset svn:keywords "Revision Date URL Author" *

clean :
	rm -f *~ *.o *.ps flex.c code_gen interpret finterpret
