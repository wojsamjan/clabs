#                                          1.X.2003
#
# Makefile do �wicze� z rozdzia�u 5 podr�cznika K&R

CFLAGS = -Wall -g
LDFLAGS = 

csources = 5.2-1.c 5.2-2.c 5.7-1.c
programs = $(csources:.c=)

.PHONY : clean

clean :
	rm -f *~ \#* core *.o $(programs)
