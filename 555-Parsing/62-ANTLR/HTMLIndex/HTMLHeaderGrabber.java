// $ANTLR 2.7.2: "index.g" -> "HTMLHeaderGrabber.java"$

import java.io.InputStream;
import antlr.TokenStreamException;
import antlr.TokenStreamIOException;
import antlr.TokenStreamRecognitionException;
import antlr.CharStreamException;
import antlr.CharStreamIOException;
import antlr.ANTLRException;
import java.io.Reader;
import java.util.Hashtable;
import antlr.CharScanner;
import antlr.InputBuffer;
import antlr.ByteBuffer;
import antlr.CharBuffer;
import antlr.Token;
import antlr.CommonToken;
import antlr.RecognitionException;
import antlr.NoViableAltForCharException;
import antlr.MismatchedCharException;
import antlr.TokenStream;
import antlr.ANTLRHashString;
import antlr.LexerSharedInputState;
import antlr.collections.impl.BitSet;
import antlr.SemanticException;

public class HTMLHeaderGrabber extends antlr.CharScanner implements HTMLIndexerTokenTypes, TokenStream
 {
public HTMLHeaderGrabber(InputStream in) {
	this(new ByteBuffer(in));
}
public HTMLHeaderGrabber(Reader in) {
	this(new CharBuffer(in));
}
public HTMLHeaderGrabber(InputBuffer ib) {
	this(new LexerSharedInputState(ib));
}
public HTMLHeaderGrabber(LexerSharedInputState state) {
	super(state);
	caseSensitiveLiterals = true;
	setCaseSensitive(false);
	literals = new Hashtable();
}

public Token nextToken() throws TokenStreamException {
	Token theRetToken=null;
tryAgain:
	for (;;) {
		Token _token = null;
		int _ttype = Token.INVALID_TYPE;
		resetText();
		try {   // for char stream error handling
			try {   // for lexical error handling
				if ((LA(1)=='<')) {
					mHEADER(true);
					theRetToken=_returnToken;
				}
				else if ((_tokenSet_0.member(LA(1)))) {
					mOTHER(true);
					theRetToken=_returnToken;
				}
				else {
					if (LA(1)==EOF_CHAR) {uponEOF(); _returnToken = makeToken(Token.EOF_TYPE);}
				else {throw new NoViableAltForCharException((char)LA(1), getFilename(), getLine(), getColumn());}
				}
				
				if ( _returnToken==null ) continue tryAgain; // found SKIP token
				_ttype = _returnToken.getType();
				_ttype = testLiteralsTable(_ttype);
				_returnToken.setType(_ttype);
				return _returnToken;
			}
			catch (RecognitionException e) {
				throw new TokenStreamRecognitionException(e);
			}
		}
		catch (CharStreamException cse) {
			if ( cse instanceof CharStreamIOException ) {
				throw new TokenStreamIOException(((CharStreamIOException)cse).io);
			}
			else {
				throw new TokenStreamException(cse.getMessage());
			}
		}
	}
}

	public final void mHEADER(boolean _createToken) throws RecognitionException, CharStreamException, TokenStreamException {
		int _ttype; Token _token=null; int _begin=text.length();
		_ttype = HEADER;
		int _saveIndex;
		
		if ((LA(1)=='<') && (LA(2)=='h') && ((LA(3) >= '1' && LA(3) <= '5')) && ((LA(4) >= '\u0003' && LA(4) <= '\u00ff'))) {
			match('<');
			match('h');
			matchRange('1','5');
			mTAG_GUTS(false);
			match('>');
		}
		else if ((LA(1)=='<') && (LA(2)=='/') && (LA(3)=='h') && ((LA(4) >= '1' && LA(4) <= '5'))) {
			match('<');
			match('/');
			match('h');
			matchRange('1','5');
			match('>');
			_ttype = HEADER_;
		}
		else if ((LA(1)=='<') && (LA(2)=='a') && (_tokenSet_1.member(LA(3))) && (_tokenSet_2.member(LA(4)))) {
			match('<');
			match('a');
			mWS(false);
			{
			switch ( LA(1)) {
			case 'n':
			{
				match("name");
				_ttype = ANCHOR;
				break;
			}
			case 'h':
			{
				match("href");
				_ttype = OTHER;
				break;
			}
			default:
			{
				throw new NoViableAltForCharException((char)LA(1), getFilename(), getLine(), getColumn());
			}
			}
			}
			{
			int _cnt11=0;
			_loop11:
			do {
				if ((_tokenSet_3.member(LA(1)))) {
					matchNot('>');
				}
				else {
					if ( _cnt11>=1 ) { break _loop11; } else {throw new NoViableAltForCharException((char)LA(1), getFilename(), getLine(), getColumn());}
				}
				
				_cnt11++;
			} while (true);
			}
			match('>');
		}
		else if ((LA(1)=='<') && (LA(2)=='/') && (LA(3)=='a') && (LA(4)=='>')) {
			match('<');
			match('/');
			match('a');
			match('>');
			_ttype = ANCHOR_;
		}
		else if ((LA(1)=='<') && ((LA(2) >= '\u0003' && LA(2) <= '\u00ff')) && (true) && (true)) {
			match('<');
			mTAG_GUTS(false);
			match('>');
			_ttype = OTHER;
		}
		else {
			throw new NoViableAltForCharException((char)LA(1), getFilename(), getLine(), getColumn());
		}
		
		if ( _createToken && _token==null && _ttype!=Token.SKIP ) {
			_token = makeToken(_ttype);
			_token.setText(new String(text.getBuffer(), _begin, text.length()-_begin));
		}
		_returnToken = _token;
	}
	
	protected final void mTAG_GUTS(boolean _createToken) throws RecognitionException, CharStreamException, TokenStreamException {
		int _ttype; Token _token=null; int _begin=text.length();
		_ttype = TAG_GUTS;
		int _saveIndex;
		
		{
		_loop15:
		do {
			if ((LA(1)=='\n')) {
				match('\n');
				newline();
			}
			else if ((_tokenSet_4.member(LA(1)))) {
				{
				match(_tokenSet_4);
				}
			}
			else {
				break _loop15;
			}
			
		} while (true);
		}
		if ( _createToken && _token==null && _ttype!=Token.SKIP ) {
			_token = makeToken(_ttype);
			_token.setText(new String(text.getBuffer(), _begin, text.length()-_begin));
		}
		_returnToken = _token;
	}
	
	protected final void mWS(boolean _createToken) throws RecognitionException, CharStreamException, TokenStreamException {
		int _ttype; Token _token=null; int _begin=text.length();
		_ttype = WS;
		int _saveIndex;
		
		{
		int _cnt22=0;
		_loop22:
		do {
			switch ( LA(1)) {
			case ' ':
			{
				match(' ');
				break;
			}
			case '\t':
			{
				match('\t');
				break;
			}
			case '\r':
			{
				match('\r');
				break;
			}
			case '\n':
			{
				match('\n');
				newline();
				break;
			}
			default:
			{
				if ( _cnt22>=1 ) { break _loop22; } else {throw new NoViableAltForCharException((char)LA(1), getFilename(), getLine(), getColumn());}
			}
			}
			_cnt22++;
		} while (true);
		}
		if ( _createToken && _token==null && _ttype!=Token.SKIP ) {
			_token = makeToken(_ttype);
			_token.setText(new String(text.getBuffer(), _begin, text.length()-_begin));
		}
		_returnToken = _token;
	}
	
	public final void mOTHER(boolean _createToken) throws RecognitionException, CharStreamException, TokenStreamException {
		int _ttype; Token _token=null; int _begin=text.length();
		_ttype = OTHER;
		int _saveIndex;
		
		{
		int _cnt19=0;
		_loop19:
		do {
			if ((LA(1)=='\n')) {
				match('\n');
				newline();
			}
			else if ((_tokenSet_5.member(LA(1)))) {
				{
				match(_tokenSet_5);
				}
			}
			else {
				if ( _cnt19>=1 ) { break _loop19; } else {throw new NoViableAltForCharException((char)LA(1), getFilename(), getLine(), getColumn());}
			}
			
			_cnt19++;
		} while (true);
		}
		if ( _createToken && _token==null && _ttype!=Token.SKIP ) {
			_token = makeToken(_ttype);
			_token.setText(new String(text.getBuffer(), _begin, text.length()-_begin));
		}
		_returnToken = _token;
	}
	
	
	private static final long[] mk_tokenSet_0() {
		long[] data = new long[8];
		data[0]=-1152921504606846984L;
		for (int i = 1; i<=3; i++) { data[i]=-1L; }
		return data;
	}
	public static final BitSet _tokenSet_0 = new BitSet(mk_tokenSet_0());
	private static final long[] mk_tokenSet_1() {
		long[] data = { 4294977024L, 0L, 0L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_1 = new BitSet(mk_tokenSet_1());
	private static final long[] mk_tokenSet_2() {
		long[] data = { 4294977024L, 71468255805440L, 0L, 0L, 0L};
		return data;
	}
	public static final BitSet _tokenSet_2 = new BitSet(mk_tokenSet_2());
	private static final long[] mk_tokenSet_3() {
		long[] data = new long[8];
		data[0]=-4611686018427387912L;
		for (int i = 1; i<=3; i++) { data[i]=-1L; }
		return data;
	}
	public static final BitSet _tokenSet_3 = new BitSet(mk_tokenSet_3());
	private static final long[] mk_tokenSet_4() {
		long[] data = new long[8];
		data[0]=-4611686018427388936L;
		for (int i = 1; i<=3; i++) { data[i]=-1L; }
		return data;
	}
	public static final BitSet _tokenSet_4 = new BitSet(mk_tokenSet_4());
	private static final long[] mk_tokenSet_5() {
		long[] data = new long[8];
		data[0]=-1152921504606848008L;
		for (int i = 1; i<=3; i++) { data[i]=-1L; }
		return data;
	}
	public static final BitSet _tokenSet_5 = new BitSet(mk_tokenSet_5());
	
	}
