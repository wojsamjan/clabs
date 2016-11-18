# ----------------------------------------------------------
# $Source: /home/nls/WEB/zjp/06-MultiCalc/RCS/Makefile,v $
# $Date: 2000/01/08 14:54:29 $
# $Revision: 1.2 $
# 
# This Makefile is distributed WITHOUT ANY WARRANTY, 
# express or implied.
# Copyright (C) 2000 Wlodek Bzyl
# ----------------------------------------------------------

PACKAGE=mfcalc
VERSION=06
YACC=bison
CC=cc

DISTFILES = Makefile main.c lex.c grammar.y

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
	enscript -GE -p$@ $<

PV = $(PACKAGE)-$(VERSION)
dist: $(DISTFILES)
	mkdir -p $(PV)
	ln $(DISTFILES) $(PV)
	tar -czhvf $(PV).tar.gz $(PV)
	rm -rf $(PV)

clean:
	rm -f *~ *.o *.ps *.log *.dvi $(PV).tar.gz \
 grammar.c grammar.h mfcalc 

# MFCALC

lex.o: lex.c grammar.c
main.o: main.c
grammar.c: grammar.y
grammar.o: grammar.c

mfcalc: main.o grammar.o lex.o
	$(CC) -o $@ $^ -lm
