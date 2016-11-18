
# $Revision: 1.5 $
# $Date: 2004/03/09 21:13:44 $

clean :
	rm -f *~ \#* *.o a.out fac *.hi out.txt index.html [1-9]*.html *.class *.java

a.out : Main.hs Factorial.hs
	ghc --make Main.hs

fac :  Main.hs Factorial.hs
	ghc -o fac --make Main.hs

Faq : Faq.jj
	javacc Faq.jj
#	javacc -debug_parser Faq.jj
#	javacc -debug_token_manager Faq.jj
	javac *.java
