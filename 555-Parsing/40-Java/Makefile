# $Source: /home/nls/WEB/zjp/40-Java/RCS/Makefile,v $
# $Date: 2000/03/28 11:11:30 $
# $Revision: 1.1 $
# 
# This Makefile is distributed WITHOUT ANY WARRANTY, express or implied.
# Copyright (C) 2000 Wlodek Bzyl
#
# Infix to postfix translator for a language consisting of sequences
# of expressions terminated by semicolons.

PACKAGE=java
VERSION=01
LEX=flex
YACC=bison
CC=cc
CFLAGS=-g -I. -I../XX-Lib

# stack + symbol tables
LIB = ../XX-Lib/mfcalc.a

DISTFILES = Makefile java-lex.l java-yacc.y \
 rr-1.y rr-2.y rr-3.y sr-1.y sr-2.y sr-3.y common-conflicts.txt

.SUFFIXES: 
.SUFFIXES: .ps .o .c .l

% : %.o
	$(CC) $(CFLAGS) -o $@ $<
%.o : %.c
	$(CC) $(CFLAGS) -c $<
%.c : %.y
	$(YACC) --verbose --defines --output $@ $<
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
java-yacc.c java-lex.c *.output *.c test.h

# Java: produce java-yacc.output. 
#   This file describes all the grammar conflicts, both those 
#   resolved by operator precedence and the unresolved ones.

java-yacc.c: java-yacc.y
	$(YACC) --verbose -o $@ $^

rr-1.c: rr-1.y
rr-2.c: rr-2.y
rr-3.c: rr-3.y

sr-1.c: sr-1.y
sr-2.c: sr-2.y
sr-3.c: sr-3.y
