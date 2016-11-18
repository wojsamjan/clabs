// $ANTLR 2.7.2: "expr_eval.g" -> "ExprParser.java"$

import antlr.TokenBuffer;
import antlr.TokenStreamException;
import antlr.TokenStreamIOException;
import antlr.ANTLRException;
import antlr.LLkParser;
import antlr.Token;
import antlr.TokenStream;
import antlr.RecognitionException;
import antlr.NoViableAltException;
import antlr.MismatchedTokenException;
import antlr.SemanticException;
import antlr.ParserSharedInputState;
import antlr.collections.impl.BitSet;

public class ExprParser extends antlr.LLkParser       implements ExprParserTokenTypes
 {

protected ExprParser(TokenBuffer tokenBuf, int k) {
  super(tokenBuf,k);
  tokenNames = _tokenNames;
}

public ExprParser(TokenBuffer tokenBuf) {
  this(tokenBuf,1);
}

protected ExprParser(TokenStream lexer, int k) {
  super(lexer,k);
  tokenNames = _tokenNames;
}

public ExprParser(TokenStream lexer) {
  this(lexer,1);
}

public ExprParser(ParserSharedInputState state) {
  super(state,1);
  tokenNames = _tokenNames;
}

	public final int  expr() throws RecognitionException, TokenStreamException {
		int value=0;
		
		int x;
		
		try {      // for error handling
			value=mexpr();
			{
			_loop3:
			do {
				switch ( LA(1)) {
				case PLUS:
				{
					match(PLUS);
					x=mexpr();
					value += x;
					break;
				}
				case MINUS:
				{
					match(MINUS);
					x=mexpr();
					value -= x;
					break;
				}
				default:
				{
					break _loop3;
				}
				}
			} while (true);
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			consume();
			consumeUntil(_tokenSet_0);
		}
		return value;
	}
	
	public final int  mexpr() throws RecognitionException, TokenStreamException {
		int value=0;
		
		int x;
		
		try {      // for error handling
			value=atom();
			{
			_loop6:
			do {
				if ((LA(1)==STAR)) {
					match(STAR);
					x=atom();
					value *= x;
				}
				else {
					break _loop6;
				}
				
			} while (true);
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			consume();
			consumeUntil(_tokenSet_1);
		}
		return value;
	}
	
	public final int  atom() throws RecognitionException, TokenStreamException {
		int value=0;
		
		Token  i = null;
		
		try {      // for error handling
			switch ( LA(1)) {
			case INT:
			{
				i = LT(1);
				match(INT);
				value=Integer.parseInt(i.getText());
				break;
			}
			case LPAREN:
			{
				match(LPAREN);
				value=expr();
				match(RPAREN);
				break;
			}
			default:
			{
				throw new NoViableAltException(LT(1), getFilename());
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			consume();
			consumeUntil(_tokenSet_2);
		}
		return value;
	}
	
	
	public static final String[] _tokenNames = {
		"<0>",
		"EOF",
		"<2>",
		"NULL_TREE_LOOKAHEAD",
		"PLUS",
		"MINUS",
		"STAR",
		"INT",
		"LPAREN",
		"RPAREN",
		"WS"
	};
	
	private static final long[] mk_tokenSet_0() {
		long[] data = { 512L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_0 = new BitSet(mk_tokenSet_0());
	private static final long[] mk_tokenSet_1() {
		long[] data = { 560L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_1 = new BitSet(mk_tokenSet_1());
	private static final long[] mk_tokenSet_2() {
		long[] data = { 624L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_2 = new BitSet(mk_tokenSet_2());
	
	}
