# ------------------------------------------------------------------
# $Source: /home/nls/WEB/zjp/07-MultiCalc/RCS/Makefile,v $
# $Date: 2000/01/08 14:57:42 $
# $Revision: 1.2 $
# 
# This file is distributed WITHOUT ANY WARRANTY, express or implied.
# Copyright (C) 2000 Wlodek Bzyl
# ------------------------------------------------------------------

PACKAGE=mfcalc
VERSION=07
YACC=bison
LEX=flex
CC=cc

DISTFILES = Makefile main.c lex.l grammar.y

CFLAGS=-g -I.

.SUFFIXES: 
.SUFFIXES: .ps .o .c .l .y

% : %.o
	$(CC) $(CFLAGS) -o $@ $<
%.o : %.c
	$(CC) $(CFLAGS) -c $<
%.c : %.l
	${LEX} -o$@ $<
%.c : %.y
	$(YACC) --defines --output $@ $<
%.ps : %.y
	enscript -GE -p$@ $<

PV = $(PACKAGE)-$(VERSION)
dist: $(DISTFILES)
	mkdir -p $(PV)
	ln $(DISTFILES) $(PV)
	tar -czhvf $(PV).tar.gz $(PV)
	rm -rf $(PV)

clean:
	rm -f *~ *.o *.ps *.log *.dvi $(PV).tar.gz \
 lex.c grammar.c grammar.h mfcalc 

# MFCALC

lex.c: lex.l
lex.o: lex.c grammar.c
grammar.c: grammar.y
grammar.o: grammar.c
main.o: main.c

mfcalc: main.o grammar.o lex.o
	$(CC) -o $@ $^ -lm
