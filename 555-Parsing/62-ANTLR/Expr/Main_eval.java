
import antlr.*;

public class Main_eval {
    public static void main(String[] args) throws Exception {
	ExprLexer lexer = new ExprLexer(System.in);
	ExprParser parser = new ExprParser(lexer);
	int x = parser.expr();
	System.out.println(x);
    }
}
