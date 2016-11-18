# (WB)                   19 listopada 2004
#
# $Revision: 1.3 $
# $Date: 2004/11/19 13:11:08 $


CFLAGS = -ggdb -pedantic -ansi -Wall

sources = binsearch zliczcbi atoi itoa trim
programs = $(sources:%.c=%)


.PHONY : clean

clean :
	rm -f core *.o *~ \#* $(programs)
