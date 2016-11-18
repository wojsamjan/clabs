
main_grammar = index.g
main_java = HTMLIndex.java

java_grammar_files = HTMLHeaderGrabber.java HTMLIndexer.java HTMLIndexerTokenTypes.java


# ---

antlrloc = .:/usr/local/share/antlr-2.7.2/antlrall.jar

main_class = $(main_java:%.java=%.class)
class_grammar_files = $(java_grammar_files:%.java=%.class)


.PHONY : generate_java_files

all : generate_java_files
	javac -classpath $(antlrloc) $(main_java) $(java_grammar_files)

generate_java_files : $(main)
#	java -cp $(antlrloc) antlr.Tool t.g
	cantlr $(main_grammar)

clean :
	rm -f *~ \#* $(java_grammar_files) $(class_grammar_files) \
 $(main_class) HTMLIndexerTokenTypes.txt

# uruchamiamy parser:
#
# export CLASSPATH=.:/usr/local/share/antlr-2.7.2/antlrall.jar
# java Main 
#   wlodek <Enter>     <- wpisujemy
#
# albo
#
# java -cp .:/usr/local/share/antlr-2.7.2/antlrall.jar Main
#   wlodek <Enter>
