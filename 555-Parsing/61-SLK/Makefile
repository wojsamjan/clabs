
clean : 
	rm -f *~ *.o Slk*

calc.o : calc.c calc.h
	cc -c -Wall $^ 

follow : calc.slk
	slk -Df $<
