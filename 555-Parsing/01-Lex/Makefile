# ----------------------------------------------------------
# $Source: /home/nls/WEB/zjp/01-Lex/RCS/Makefile,v $
# $Date: 2000/01/07 11:28:59 $
# $Revision: 1.1 $
# 
# A generic Makefile for compiling FLEX programs.
# It is distributed WITHOUT ANY WARRANTY, express or implied.
# Copyright (C) 2000 Wlodek Bzyl
# ----------------------------------------------------------

CC = gcc -g
LEX = flex
YACC = bison
#CFLAGS = -DYYDEBUG=1

LSOURCES = 00.l 01.l 02.l 03.l 04.l 05.l 06.l 07.l
TESTFILES = test007.txt

PROGRAMS = $(LSOURCES:.l=)
CSOURCES = $(LSOURCES:.l=.c)
OBJS = $(CSOURCES:.c=.o)

all: ${LPROGRAMS}

dist zjp1999l.tar.gz:
	tar zcvf zjp1999l.tar.gz Makefile ${LSOURCES} ${TESTFILES}

clean:
	rm -f *~ ${CSOURCES} ${OBJS} ${PROGRAMS} zjp1999l.tar.gz

#.SUFFIXES: 
.SUFFIXES: .o .c .l .y

%.c : %.l
	${LEX} -o$@ $<
% : %.o
	$(CC) $(CFLAGS) -o $@ $<
