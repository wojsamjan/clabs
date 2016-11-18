# ----------------------------------------------------------
# $Source: /home/nls/WEB/zjp/XX-Lib/RCS/Makefile,v $
# $Date: 2000/01/08 14:20:16 $
# $Revision: 1.1 $
# 
# This Makefile is distributed WITHOUT ANY WARRANTY, express 
# or implied.
# Copyright (C) 2000 Wlodek Bzyl
#
# Building library for mutli-function calculator.
# ----------------------------------------------------------

PACKAGE=mfcalc-lib
VERSION=000
YACC=bison
LEX=flex
CC=cc

LIBSOURCES=genlib.c exception.c symtab.c stack.c
LIBHEADERS=$(BNFSOURCES:.c=.h)
LIBOBJECTS=$(LIBSOURCES:.c=.o)
LIB=mfcalc.a
CFLAGS=-g -I.

DISTFILES = Makefile $(LIBSOURCES) $(LIBHEADERS)

.SUFFIXES: 
.SUFFIXES: .ps .o .c .y

% : %.o
	$(CC) $(CFLAGS) -o $@ $<
%.o : %.c
	$(CC) $(CFLAGS) -c $<
%.c : %.l
	${LEX} -o$@ $<
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
	@rm -f *~ *.o *.ps *.log *.dvi $(PV).tar.gz

# Constructing library

genlib.o: genlib.c genlib.h exception.h
exception.o: exception.c exception.h genlib.h
symtab.o: symtab.c symtab.h exception.h genlib.h
stack.o: stack.c stack.h exception.h genlib.h

# Entry to reconstruct the library archive

lib $(LIB): $(LIBOBJECTS)
	-rm -f $(LIB)
	ar cr $(LIB) $(LIBOBJECTS)
	ranlib $(LIB)
