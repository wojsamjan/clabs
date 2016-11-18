# home
CFLAGS=-I /usr/lib/ruby/1.8/i386-linux
# manta
#CFLAGS=-I/usr/lib/ruby/1.8/i686-linux
#LDFLAGS=
#LIBS=

all : foo.so example.so

CFLAGS=-I/usr/lib/ruby/1.8/i686-linux
#CFLAGS=-I/usr/lib/ruby/1.8/i386-linux

foo.o : foo.c

foo_wrap.c : foo.i
	swig -ruby foo.i

foo_wrap.o : foo_wrap.c
	gcc -c foo_wrap.c -I/usr/lib/ruby/1.8/i686-linux

foo.so : foo.o foo_wrap.o
	gcc -shared foo.o foo_wrap.o -o foo.so

# irb
# > require 'foo'
# > Foo.bar  # => 2.7172

example.o : example.c

example_wrap.c : example.i
	swig -ruby example.i

example_wrap.o : example_wrap.c
	gcc -c example_wrap.c -I/usr/lib/ruby/1.8/i686-linux

example.so : example.o example_wrap.o
	gcc -shared example.o example_wrap.o -o example.so

clean :
	rm -f *~ \#* *_wrap.c *.o *.so
