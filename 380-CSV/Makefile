CFLAGS = -std=c11 -Wall

compare = cmp -s

csv1.o : csv1.h csv1.h

csv2.o : csv2.c csv2.h

csv.o : csv.c csv2.h

csvtest1 : csvtest1.o csv1.o
	$(CC) $^ -o $@

csvtest2 : csvtest2.o csv2.o
	$(CC) $^ -o $@

csvtest3 : csvtest3.o csv2.o
	$(CC) $^ -o $@

clean :
	rm -f *~ \#* core csv[1].o csvtest[123].o csvtest[123] [123456789]

# Można tak testować

make_test = @ $(1) < test-input/$(3) > $(3) ; \
	if $(compare) $(3) $(2)/$(3) ; then \
           echo "OK" ; else echo "ŹLE" ; fi

test1 : csvtest1
	@printf "Test 2. Pola ograniczone znakiem cudzysłowu..\t"
	$(call make_test,./csvtest1,ok,2)

# a tak jest prościej (ale czy lepiej?)

test2 : csvtest2
	@printf "Test 2. Pola ograniczone znakiem cudzysłowu..\t"
	@./csvtest2 < test-input/2 > 2
	@if $(compare) 2 ok/2 ; then echo OK ; else "ŹLE" ; fi
