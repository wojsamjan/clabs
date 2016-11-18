
all : Makefile
	make
	./run.rb

example_wrap.c : example.i
	swig -ruby example.i

Makefile : extconf.rb example_wrap.c example.c
	ruby extconf.rb

clean :
	rm -f *~ \#* *_wrap.c *.o *.so Makefile

