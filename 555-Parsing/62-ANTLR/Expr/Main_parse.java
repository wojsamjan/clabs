
import antlr.*;

public class Main_parse {
    public static void main(String[] args) throws Exception {
        ExprLexer lexer = new ExprLexer(System.in);
        ExprParser parser = new ExprParser(lexer);
        parser.expr();
    }
}
