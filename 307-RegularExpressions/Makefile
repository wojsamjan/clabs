#
# Brian W. Kernighan, Rob Pike
# Lekcja programowania, 9.2 Wyrażenia regularne
# WNT 2002

CC=gcc
CFLAGS=-Wall -g

csources = main.c sgrep.c 

programs = $(csources:.c=)


sgrep : main.o sgrep.o

sgrep.o : sgrep.c sgrep.h

main.o : main.c sgrep.h


# zob. http://www.gnu.org/software/make/manual/make.html#Pattern-Rules

%.ps : %.c
	iconv -f utf8 -t latin2 $< | a2ps -X iso2 -o $@


.PHONY : clean 

all : $(programs)

clean:
	rm -f core \#* *~ *.o *.ps $(programs)
