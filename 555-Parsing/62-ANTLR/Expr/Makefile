
main_grammars = expr_parse.g expr_eval.g expr_tree_eval.g

prefix1 = Expr
prefix2 = ExprTree

main_java = Main_parse.java Main_eval.java Main_tree_eval.java


# ---

java_grammar_files1 = $(prefix1)Lexer.java \
 $(prefix1)Parser.java \
 $(prefix1)ParserTokenTypes.java

java_grammar_files2 = \
 $(prefix2)Parser.java \
 $(prefix2)ParserTokenTypes.java

class_grammar_files = $(java_grammar_files1:%.java=%.class) \
 $(java_grammar_files2:%.java=%.class)

main_class = $(main_java:%.java=%.class)

antlrloc = .:/usr/local/share/antlr-2.7.2/antlrall.jar

help :
	@echo ""
	@echo "Usage:  make [ expr_parse | expr_eval | expr_tree_eval ]"
	@echo ""

.PHONY : parse eval tree_eval expr_parse expr_eval expr_tree_eval generate_java_files

expr_parse : parse
	javac -classpath $(antlrloc) Main_parse.java $(java_grammar_files1)

expr_eval : eval
	javac -classpath $(antlrloc) Main_eval.java $(java_grammar_files1)

expr_tree_eval : tree_eval
	javac -classpath $(antlrloc) Main_tree_eval.java \
 $(java_grammar_files1) $(java_grammar_files2)

parse : Main_parse.java
	cantlr expr_parse.g

eval : Main_eval.java
	cantlr expr_eval.g

tree_eval : Main_tree_eval.java
	cantlr expr_tree_eval.g

clean :
	rm -f *~ \#* $(java_grammar_files1) $(java_grammar_files2) \
 $(class_grammar_files) $(main_class) \
 {$(prefix1),$(prefix2)}ParserTokenTypes.txt

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
