
import antlr.*;
import antlr.collections.*;

public class Main_tree_eval {
    public static void main(String[] args) throws Exception {    
        ExprLexer lexer = new ExprLexer(System.in);
        ExprParser parser = new ExprParser(lexer);
        parser.expr();
        AST t = parser.getAST();
        System.out.println(t.toStringTree());
        ExprTreeParser treeParser = new ExprTreeParser();
        int x = treeParser.expr(t);
        System.out.println(x);
    }    
}
