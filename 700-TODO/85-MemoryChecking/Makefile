#   Plik:  Makefile
# Wersja:  19 XI 2002 */


include ../make/common.mk

ARCHIVE = memory_checking
DISTFILES = test1.c test2.c test3.c test4.c
PROGRAMS = $(DISTFILES:%.c=%) 

LOADLIBES = /usr/local/share/lib/memchk.o -lcii

test1 : test1.o
test2 : test2.o
test3 : test3.o
test4 : test4.o

.PHONY: all

all : test1 test2 test3 test4
