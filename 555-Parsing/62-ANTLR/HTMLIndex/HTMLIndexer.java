// $ANTLR 2.7.2: "index.g" -> "HTMLIndexer.java"$

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

import java.io.*;

public class HTMLIndexer extends antlr.LLkParser       implements HTMLIndexerTokenTypes
 {

	PrintStream output;
	String prefix = ".";
	PrintStream indexOutput = System.out;
	String fileName;
	String bookmarkPrefix = "_bb";

	public void setOutputStream(PrintStream o) {
		output = o;
	}

	public void setFilePrefix(String p) {
		prefix = p;
	}

	public void setFileName(String f) {
		fileName = f;
	}

	public void printIndexEntry(int oldlevel, int level, int bookmark, String section) {
	}

protected HTMLIndexer(TokenBuffer tokenBuf, int k) {
  super(tokenBuf,k);
  tokenNames = _tokenNames;
}

public HTMLIndexer(TokenBuffer tokenBuf) {
  this(tokenBuf,1);
}

protected HTMLIndexer(TokenStream lexer, int k) {
  super(lexer,k);
  tokenNames = _tokenNames;
}

public HTMLIndexer(TokenStream lexer) {
  this(lexer,1);
}

public HTMLIndexer(ParserSharedInputState state) {
  super(state,1);
  tokenNames = _tokenNames;
}

	public final void document() throws RecognitionException, TokenStreamException {
		
		Token  h = null;
		Token  sec = null;
		Token  a = null;
		Token  oo = null;
		Token  a_ = null;
		Token  h_ = null;
		Token  o = null;
		Token  a1 = null;
		Token  a1_ = null;
		
			String section="";
			String indexSection="";
			int n=1;	// bookmark number for <a> tag
			int level=0, oldlevel = -1;
		
		
		try {      // for error handling
			{
			_loop7:
			do {
				switch ( LA(1)) {
				case HEADER:
				{
					section=""; indexSection="";
					h = LT(1);
					match(HEADER);
					{
					int _cnt6=0;
					_loop6:
					do {
						switch ( LA(1)) {
						case OTHER:
						{
							sec = LT(1);
							match(OTHER);
							
											section += sec.getText();
											indexSection += sec.getText();
											
							break;
						}
						case ANCHOR:
						{
							a = LT(1);
							match(ANCHOR);
							
											boolean ignoreAnchor=false;
											if ( !a.getText().startsWith("<a name=\""+bookmarkPrefix) ) {
												section += a.getText();
												ignoreAnchor=true;
											}
											
							{
							_loop5:
							do {
								if ((LA(1)==OTHER)) {
									oo = LT(1);
									match(OTHER);
									
														section += oo.getText();
														indexSection += oo.getText();
														
								}
								else {
									break _loop5;
								}
								
							} while (true);
							}
							a_ = LT(1);
							match(ANCHOR_);
							if ( !ignoreAnchor ) section += a_.getText();
							break;
						}
						case ANCHOR_:
						{
							match(ANCHOR_);
							
											reportError("<a href=...> nested in header tag");
											
							break;
						}
						case HEADER:
						{
							match(HEADER);
							
											reportError("mismatched or nested header tag");
											
							break;
						}
						default:
						{
							if ( _cnt6>=1 ) { break _loop6; } else {throw new NoViableAltException(LT(1), getFilename());}
						}
						}
						_cnt6++;
					} while (true);
					}
					h_ = LT(1);
					match(HEADER_);
					
									// write modified header back out to file
									output.print(
										h.getText()+
										"<a name=\""+bookmarkPrefix+n+"\">"+
										section+
										"</a>"+
										h_.getText());
					
									level = h.getText().charAt(2)-'1';
					
									if ( level<oldlevel ) {
										// close off old list
										indexOutput.println("</ul>");
									}
					
									// add index entry
									if ( level>oldlevel ) {
										// make new <ul>
										indexOutput.println("<ul>");
									}
					
									indexOutput.println(
										"<li>"+
										"<a href=\""+
											prefix+"/"+fileName+"#"+bookmarkPrefix+n+
										"\">"+
										indexSection+
										"</a>"+
										"</li>");
					
									oldlevel = level;
									n++;
								
					break;
				}
				case OTHER:
				{
					o = LT(1);
					match(OTHER);
					output.print(o.getText());
					break;
				}
				case ANCHOR:
				{
					a1 = LT(1);
					match(ANCHOR);
					output.print(a1.getText());
					break;
				}
				case ANCHOR_:
				{
					a1_ = LT(1);
					match(ANCHOR_);
					output.print(a1_.getText());
					break;
				}
				default:
				{
					break _loop7;
				}
				}
			} while (true);
			}
			
					// close off index lists
					for ( ; level>=0; level-- ) {
						indexOutput.println("</ul>");
					}
					
		}
		catch (RecognitionException ex) {
			reportError(ex);
			consume();
			consumeUntil(_tokenSet_0);
		}
	}
	
	
	public static final String[] _tokenNames = {
		"<0>",
		"EOF",
		"<2>",
		"NULL_TREE_LOOKAHEAD",
		"HEADER",
		"OTHER",
		"ANCHOR",
		"ANCHOR_",
		"HEADER_",
		"TAG_GUTS",
		"WS"
	};
	
	private static final long[] mk_tokenSet_0() {
		long[] data = { 2L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_0 = new BitSet(mk_tokenSet_0());
	
	}
