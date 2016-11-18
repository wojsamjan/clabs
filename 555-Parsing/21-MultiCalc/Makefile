# ----------------------------------------------------------
# $Source: /home/nls/WEB/mfcalc/RCS/Makefile,v $
# $Date: 2000/01/02 14:14:45 $
# $Revision: 1.6 $
# ----------------------------------------------------------
# This Makefile belongs to the MFCALC package.
# It is distributed WITHOUT ANY WARRANTY, express or implied.
# Copyright (C) 2000 Wlodek Bzyl
# ----------------------------------------------------------

PACKAGE=mfcalc
VERSION=002
YACC=bison
CC=cc

DISTFILES = Makefile exception.c exception.h genlib.c genlib.h \
 symtab.c symtab.h tsymtab.c \
 mfcalc.y common.h init.c input.c input.h lex.c main.c 

LIBSOURCES=genlib.c exception.c symtab.c input.c
LIBHEADERS=$(BNFSOURCES:.c=.h)
LIBOBJECTS=$(LIBSOURCES:.c=.o)
LIB=symtablib.a
CFLAGS=-g -I.

.SUFFIXES: 
.SUFFIXES: .ps .o .c .y

% : %.o
	$(CC) $(CFLAGS) -o $@ $<
%.o : %.c
	$(CC) $(CFLAGS) -c $<
%.c : %.y
	$(YACC) --defines --output $@ $<
%.ps : %.y
	enscript -Xlatin2 -GE -p$@ $<

PV = $(PACKAGE)-$(VERSION)
dist: $(DISTFILES)
	mkdir -p $(PV)
	ln $(DISTFILES) $(PV)
	tar -czhvf $(PV).tar.gz $(PV)
	rm -rf $(PV)

clean:
	rm -f *~ *.o *.ps *.log *.dvi $(PV).tar.gz $(LIB)\
 mfcalc{,.c,.h} tsymtab

# Constructing library

genlib.o: genlib.c genlib.h exception.h
exception.o: exception.c exception.h genlib.h
symtab.o: symtab.c symtab.h exception.h genlib.h

# Entry to reconstruct the library archive

$(LIB): $(LIBOBJECTS)
	-rm -f $(LIB)
	ar cr $(LIB) $(LIBOBJECTS)
	ranlib $(LIB)

# MFCALC

init.o: init.c common.h mfcalc.c symtab.h
lex.o: lex.c common.h mfcalc.c symtab.h
main.o: main.c common.h symtab.h
mfcalc.y: common.h symtab.h

mfcalc: main.o mfcalc.o lex.o init.o $(LIB)
	$(CC) -o $@ $^ -lm

# Tests.

tsymtab: tsymtab.o symtablib.a
	$(CC) $(CFLAGS) -o $@ $^
