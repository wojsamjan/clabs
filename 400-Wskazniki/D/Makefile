CFLAGS = -Wall -std=c11

csources = nsort.c psort.c
programs = $(csources:.c=)
data = nunsorted.txt punsorted.txt

.PHONY : clean

clean :
	rm -f *~ \#* core *.o $(programs) nsorted.txt psorted.txt
