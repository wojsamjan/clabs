
libc_wrap.c : libc.i
	swig -ruby libc.i

Makefile : extconf.rb libc_wrap.c
#       ruby extconf.rb --with-tcl-include=/usr/include/tcl8.4
	ruby extconf.rb

clean :
	rm -f *~ \#* *_wrap.c *.o *.so source.txt dest.txt

