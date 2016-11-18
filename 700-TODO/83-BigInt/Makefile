#   Plik:  Makefile
# Wersja:  5 XI 2002
#  Autor:  W. Bzyl, <matwb@univ.gda.pl>

include ../make/common.mk

headers = list.h atom.h
sources = test1.c test2.c

programs = $(sources:%.c=%) 
archive = 80-BigInt
distfiles =$(sources) $(headers)

test1 : test1.o
test2 : test2.o

.PHONY: all

all: test1 test2

programs.ps: $(headers) $(sources)
	enscript -GE -p$@ $^

programs.ljet4 : programs.ps
	gs -dNOPAUSE -dBATCH -sDEVICE=ljet4 -sOutputFile=programs.ljet4 $<
