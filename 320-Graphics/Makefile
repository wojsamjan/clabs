# 
#  $Date: 2004/05/04 17:12:43 $
#  $Revision: 1.1 $
#
# GPROF -- narzêdzie do profilowania wykonywania programu.
#
#   Program ten drukuje raport z pliku ¶ledzenia przebiegu
#   wykonywania (gmon.out), który powstaje w czasie dzia³ania
#   programu skompilowanego z opcj± `-pg'
#   Zapoznaj siê ze stron± podrêcznika opisuj±c ten program.
#
#   Po wykonaniu, któregokolwiek z programów wykonaj polecenia:
#     
#    gprof --file-info <nazwa programu>
#    gprof --brief --flat <nazwa programu>
#    gprof --flat <nazwa programu> | less
#    gprof <nazwa programu> | less
#    gprof --brief <nazwa programu> | less
#    gprof --annotated-source <nazwa programu> | less

sources = Makefile 
headers = 
programs = arc1 arc2 drawcirc drawcbox oneline drawbox house 

csources = $(programs:%=%.c)

#cs-includes = /usr/local/include/cslib
#cs-library = /usr/local/include/cslib/cslib.a

#CFLAGS = -ggdb -pg -I$(cs-includes)
#LDFLAGS =
#LDLIBS =  -pg $(cs-library) -lm

CC = gccx

all : $(programs)

arc1 : arc1.o
arc2 : arc2.o
drawcirc : drawcirc.o
drawcbox : drawcbox.o
oneline : oneline.o
drawbox : drawbox.o
house : house.o

.PHONY : clean

clean :
	rm -f core *.o *~ *.ps gmon.out gmon.sum $(programs)
