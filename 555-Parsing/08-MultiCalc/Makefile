# $Source: /home/nls/WEB/zjp/09-MultiCalc/RCS/Makefile,v $
# $Date: 2000/01/08 14:45:27 $
# $Revision: 1.3 $
# 
# This Makefile is distributed WITHOUT ANY WARRANTY, express or implied.
# Copyright (C) 2000 Wlodek Bzyl
#
# Building calculator with arbitrary variable names and 
# built-in functions and constants.

PACKAGE=mfcalc
VERSION=08
YACC=bison
LEX=flex
CC=cc
CFLAGS=-g -I. -I../XX-Lib

# stack + symbol tables
LIB = ../XX-Lib/mfcalc.a

DISTFILES = Makefile main.c grammar.y lex.l init.h init.c

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
	@rm -f *~ *.o *.ps *.log *.dvi $(PV).tar.gz \
 grammar{,.c,.h} lex.c mfcalc

# MFCALC

init.o: init.c init.h grammar.c
lex.c: lex.l grammar.c
lex.o: lex.c init.h grammar.c
main.o: main.c init.h
grammar.y: init.h

mfcalc: main.o grammar.o lex.o init.o $(LIB)
	$(CC) -o $@ $^ -lm
