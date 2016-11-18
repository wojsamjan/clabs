
# ¦cie¿ki do plików nag³ówkowych i biblioteki `cii',
# której autorem jest David R. Hanson (Princeton University).
# ¬ród³a s± dostêpne z ftp.cs.princeton.edu/pub/packages/cii.

cii-includes = /usr/local/include/cii
cii-lib = /usr/local/lib

archive ?= kjp2
distfiles ?= 
programs ?=  

CC = cc
LD = cc

CFLAGS = -Wall -ggdb -I $(cii-includes)
LDFLAGS = -Wall -ggdb -L $(cii-lib)
#LOADLIBES = /usr/local/share/lib/memchk.o -lcii
LOADLIBES = -lcii

.PHONY: clean dist

clean :
	rm -f *~ \#* core *.o $(programs) $(archive).tar.gz \
programs.{ps,ljet4}

dist :
	tar zcvf $(archive).tar.gz Makefile $(distfiles)
