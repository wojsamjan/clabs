
CFLAGS = -g -Wall

all : liberr.a

liberr.o : liberr.c

liberr.a : liberr.o
	ar rcs liberr.a liberr.o

liberr.so : liberr.c
	rm -f liberr.a liberr.so
	gcc -c -fPIC liberr.c -o liberr.o 
	gcc -shared -Wl,-soname,liberr.so -o liberr.so.1.0.1 liberr.o
	ln -s liberr.so.1.0.1 liberr.so

errtest.o : errtest.c liberr.h


errtest-a: liberr.a errtest.o
	rm -f liberr.so.1.0.1 liberr.so
	$(CC) $(CFLAGS) errtest.o -o errtest-a -L. -lerr

errtest-so: liberr.so errtest.o
	gcc errtest.c -o errtest-so -L. -lerr
	@echo "-----------"
	@echo "Running ldd"
	ldd ./errtest-so
	@echo "-----------"
	@echo "Now you can run errtest-so with:"
	@printf '  LD_LIBRARY_PATH=$$(pwd) ./errtest-so'
	@echo ""

run :
	LD_LIBRARY_PATH=$(pwd) ./errtest-so

clean :
	rm -f *~ \#* *.o *.a *.so *.so.* errtest{-a,-so,.log}
