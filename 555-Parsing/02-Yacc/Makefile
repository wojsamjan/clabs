# ----------------------------------------------------------
# $Source: /home/nls/WEB/zjp/01-Lex/RCS/Makefile,v $
# $Date: 2000/01/07 11:28:59 $
# $Revision: 1.1 $
# 
# A simplified Makefile for compiling the BISON programs
# listed below.
# It is distributed WITHOUT ANY WARRANTY, express or implied.
# Copyright (C) 2000 Wlodek Bzyl
# ----------------------------------------------------------

CC = gcc -g
LEX = flex
YACC = bison
#CFLAGS = -DYYDEBUG=1

YSOURCES = 05.y 06.y 07.y 08.y 09.y \
 10.y 11.y 12.y 13.y 14.y 15.y 16.y 17.y 20.y 21.y
LSOURCES = 05.l 06.l 08.l

PROGRAMS = $(YSOURCES:.y=)
CSOURCES = $(YSOURCES:.y=.c)
OBJS = $(CSOURCES:.c=.o)

all: ${LPROGRAMS}

dist zjp1999y.tar.gz:
	tar zcvf zjp1999y.tar.gz Makefile ${YSOURCES} ${LSOURCES}

clean:
	rm -f *~ parser.[hco] scanner.[co] *.output \
${PROGRAMS} ${CSOURCES} ${OBJS} zjp1999y.taz

#.SUFFIXES: 
.SUFFIXES: .o .c .l .y

%.c : %.y
	${YACC} --defines --output parser.c $<
%.c : %.l
	${LEX} -o$@ $<
% : %.o
	$(CC) $(CFLAGS) -o $@ $<

# Examples

05: 05.y 05.l
	${YACC} --defines --output parser.c $@.y
	${LEX} -oscanner.c $@.l
	${CC} -c parser.c scanner.c
	${CC} -o$@ parser.o scanner.o
06: 06.y 06.l
	${YACC} --defines --output parser.c $@.y
	${LEX} -oscanner.c $@.l
	${CC} -c parser.c scanner.c
	${CC} -o$@ parser.o scanner.o
07: 07.y
	${YACC} --output parser.c $@.y
	${CC} -c parser.c
	${CC} -o$@ parser.o -lm
08: 08.y 08.l
	${YACC} --defines --output parser.c $@.y
	${LEX} -oscanner.c $@.l
	${CC} -c parser.c scanner.c
	${CC} -o$@ parser.o scanner.o -lm
09: 09.y
	${YACC} --debug --verbose --output parser.c $@.y
	${CC} -c parser.c
	${CC} -o$@ parser.o
10: 10.y
	${YACC} --verbose --output parser.c $@.y
	${CC} -c parser.c
	${CC} -o$@ parser.o
11: 11.y
	${YACC} --verbose --output parser.c $@.y
	${CC} -c parser.c
	${CC} -o$@ parser.o
12: 12.y
	${YACC} --verbose --output parser.c $@.y
	${CC} -c parser.c
	${CC} -o$@ parser.o
13: 13.y
	${YACC} --verbose --output parser.c $@.y
	${CC} -c parser.c
	${CC} -o$@ parser.o
14: 14.y
	${YACC} --verbose --output parser.c $@.y
	${CC} -c parser.c
	${CC} -o$@ parser.o
15: 15.y
	${YACC} --verbose --output parser.c $@.y
	${CC} -c parser.c
	${CC} -o$@ parser.o
16: 16.y
	${YACC} --verbose --output parser.c $@.y
	${CC} -c parser.c
	${CC} -o$@ parser.o
17: 17.y
	${YACC} --verbose --output parser.c $@.y
	${CC} -c parser.c
	${CC} -o$@ parser.o
