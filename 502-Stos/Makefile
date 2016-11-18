# W. Bzyl                                    12.XII.1999
#
# Makefile do przykladow omawianych na wykladzie
# 
# abstrakcyjne typy danych, nieprzezroczyste typy danych

CFLAGS = -g -Wall
CC = gccx

sources = stack.h stack2.c stack1.c stack.c rpn-simulation.c
programs = rpn2 rpn1 rpn

all : rpn rpn1 rpn2

stack2.o : stack2.c stack.h
stack1.o : stack1.c stack.h
stack.o : stack.c stack.h
rpn-simulation.o : rpn-simulation.c

rpn2 : rpn-simulation.o stack2.o
	$(CC) -o $@ $^
rpn1 : rpn-simulation.o stack1.o
	$(CC) -o $@ $^
rpn : rpn-simulation.o stack.o
	$(CC) -o $@ $^


.PHONY : clean

clean:
	rm -f core *.o *~ \#* *.ps *.ljet4 $(programs)

all.ps : $(sources)
#	enscript -f PLTypewriter10-Regular@12 -X latin2 -GE -p$@ $^
	enscript --color -v -f Courier@12 -X latin2 -GE -p$@ $^

all.ljet4 : all.ps
	gs -dNOPAUSE -sDEVICE=ljet4 -sOutputFile=all.ljet4 -dBATCH all.ps
