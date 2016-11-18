# $Source: /home/nls/WEB/zjp/03-RecDescent/RCS/Makefile,v $
# $Date: 2000/02/20 19:09:19 $
# $Revision: 1.2 $
# 
# This Makefile is distributed WITHOUT ANY WARRANTY, express or implied.
# Copyright (C) 2000 Wlodek Bzyl
#
# Infix to postfix translator for a language consisting of sequences
# of expressions terminated by semicolons.

PACKAGE=ip
VERSION=01
LEX=flex
CC=cc
CFLAGS=-g -I. -I../XX-Lib

# stack + symbol tables
LIB = ../XX-Lib/mfcalc.a

DISTFILES = Makefile main.c grammar.c lex.l common.h

.SUFFIXES: 
.SUFFIXES: .ps .o .c .l

% : %.o
	$(CC) $(CFLAGS) -o $@ $<
%.o : %.c
	$(CC) $(CFLAGS) -c $<
%.c : %.l
	${LEX} -o$@ $<
%.ps : %.y
	enscript -Xlatin2 -GE -p$@ $<

PV = $(PACKAGE)-$(VERSION)
dist: $(DISTFILES)
	mkdir -p $(PV)
	ln $(DISTFILES) $(PV)
	tar -czhvf $(PV).tar.gz $(PV)
	rm -rf $(PV)

clean:
	@rm -f *~ *.o *.ps *.log *.dvi $(PV).tar.gz lex.c ip

# IP

lex.c: lex.l common.h
lex.o: lex.c
grammar.o: grammar.c common.h
main.o: main.c

ip: main.o grammar.o lex.o $(LIB)
	$(CC) -o $@ $^
