#
#  $Date: 2004/10/08 12:29:47 $
#  $Revision: 1.2 $
#

CFLAGS = -Wall -g

sources =  main.c grep.c
headers =  grep.h

objects = $(sources:.c=.o)

sgrep : main.o grep.o
	$(CC) $^ -o $@

grep.o : grep.c grep.h

main.o : main.c grep.h


.PHONY : clean 

clean:
	rm -f core \#* *~ $(objects) sgrep grep.ps

grep.ps: $(sources) $(headers) Makefile
	enscript -GE -p$@ $^
