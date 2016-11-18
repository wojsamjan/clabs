#
#  $URL: http://manta.univ.gda.pl/svn/wb/labs/c/605-Ncurses/Makefile $
#  $Revision: 232 $

CFLAGS=-Wall -ansi -ggdb
LDLIBS=-lncursesw
#LOADLIBES=-lncursesw

all : keypressed hello hello-utf

keypressed: keypressed.c
	$(CC) $(CFLAGS) $* $? -o $@

hello: hello.c

hello-utf: hello-utf.c

clean :
	rm -f *~ \#*~ a.out *.o keypressed hello hello-utf 

.PHONY : clean


### curses & utf-8
#
# First of all, at least on my FC1 box, there are two ncurses
# installations. One in <ncurses/ncurses.h> and one in
# <ncursesw/ncurses.h> you must make sure you include the latter, or the
# unicode stuff will not work at all. I have absolutely no idea why this
# version is not the default.
# 
# 
# You have to remember to link with -lncursesw instead of -lncurses.
# 
# Also don't forget to issue the call to setlocale(LC_ALL,"") in the
# beginning of the program. Although I suppose you already do. :-)
# 
# 
# Next, you have to decide wether you want the application to work with
# and print wide strings (wchar_t *) or UTF-8 strings (char *). It's a
# matter of taste really. Both methods work and has their respective
# drawbacks and advantages. Usually, especially when changing existing
# code, it's much easier to use UTF-8. Nothing prevents you from using a
# combination either. Using UTF-8 most everywhere but using wchar_t where
# it's needed specifically.
# 
# 
# If you want to use UTF-8, you're pretty much done! Just work with the
# UTF-8 strings just like any other string. Just remember to use wcslen()
# instead of strlen() if you want the number of characters. This is
# particularily important when doing formatting for a curses app.
# 
# 
# If you want to use whcar_t, read up on the mbstowcs() and wcstombs()
# functions. mbs means "system encoding" pretty much (which, unless you're
# on a legacy system, means UTF-8). wcs is a wchar_t string. Then you can
# simply use addwstr() instead of addstr() etc. All of the old
# "char"-based functions has unicode-aware equivalents.

## ???
#  For screen layout purposes, don't you really want to use wcswidth()
#  instead of wcslen()? The former gives you the number of character cells
#  that a string will move the cursor forward on a typical UTF-8 terminal,
#  the latter gives you merely the number of characters, each of which may
#  consume 0, 1, or 2 character cells.
