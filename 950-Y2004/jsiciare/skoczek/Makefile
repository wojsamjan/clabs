PROGRAMS=index.cgi konsola skoczek

CC=gcc
CFLAGS=-Wall -pedantic -ansi
LDFLAGS=

all : clean $(PROGRAMS) tidy

#% : %.c
#	$(CC) $(CFLAGS) $(LDFLAGS) -o index$(SUFIX) $<


skoczek : skoczek.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o skoczek $<


konsola.o : konsola.c

index.o : index.c

knightmoves.o : knightmoves.c knightmoves.h


konsola : konsola.o knightmoves.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

index.cgi : index.o knightmoves.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^






plugin : xindex xknightmoves1.so xknightmoves2.so


xknightmoves1.so : xknightmoves1.c
	$(CC) -fPIC xknightmoves1.c -c
	$(CC) -shared xknightmoves1.o -o xknightmoves1.so

xknightmoves2.so : xknightmoves2.c
	$(CC) -fPIC xknightmoves2.c -c
	$(CC) -shared xknightmoves2.o -o xknightmoves2.so


xindex :
	$(CC) -rdynamic xindex.c -ldl -o index.cgi
 




# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

.PHONY : clean

clean:
	@rm -f *~ \#* core *.{o,so} $(PROGRAMS)
	@echo -e "\033[1;31mUsuniêto wszystkie niepotrzebne pliki\033[m"

tidy:
	@rm -f *~ \#* core *.o

