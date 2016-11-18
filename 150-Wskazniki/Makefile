#
#                                     14.11.2015
# Makefile do przykladow omawianych na wykladzie

CC = gccx
CFLAGS = -std=c11 -Wall -Wno-uninitialized
LDFLAGS = -lm

% : %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

#      -- uzupełnić
# p1.c
# p2.c
# p3.c

#      -- uzupełnione wersje
# poly1.c -- przekazywanie wartości między funkcjami
# poly2.c -- wykorzystanie struktur
# poly3.c -- wskaźniki do struktur

csources = swap.c swap2.c \
 struct1.c struct2.c struct3.c \
 p1.c p2.c p3.c poly1.c poly2.c poly3.c \
 rps.c rps2.c rps3.c

programs = $(csources:.c=)

.PHONY : clean

clean :
	rm -f core a.out *.o *~ $(programs)

helpers.o : helpers.c helpers.h

rps3.o : rps3.c helpers.h

rps3 : rps3.o helpers.o
	$(CC) -o rps3 $^ -lm
