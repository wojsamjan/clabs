#
#  $URL: http://manta.univ.gda.pl/svn/wb/labs/c/520-BigInt/Makefile $
#  $Revision: 195 $
# 

CC = gccx
CFLAGS = -Wall -ggdb -ansi

bigint.o : bigint.c bigint.h

bigfact.o : bigfact.c bigint.h

bigfactorial : bigfactorial.o bigint.o
	$(CC) $(CFLAGS) $^ -o $@

clean : 
	rm -f *~ *.o bigfactorial
