
using System ;

class Scanner {

internal
Scanner ( string  input,
          ClcLog  log )
{
    this.log = log;
    expr = input.ToCharArray();
    length = expr.Length;
    start = 0;
}

public double      get_attribute ()       { return  last_attribute; }

protected ClcLog   log;

private double  attribute;
private double  last_attribute;
private char[]  expr;
private int     start;
private int     length;

public 
short get ()
{
    short    token;
    int      end; 

    while ( start < length  &&  Char.IsWhiteSpace ( expr [start] ) ) {
        ++start;
    }                       
    last_attribute = attribute; 
                        
    if ( start >= length ) {
        token = ClcConstants.END_OF_SLK_INPUT_;
    } else if ( Char.IsDigit ( expr [start] )  ||  expr [start] == '.' ) {
        token = ClcConstants.NUMBER_;
        end = start;
        while ( Char.IsDigit ( expr [end] )  ||  expr [end] == '.' ) {
            ++end;
            if ( end == length ) {
                break; 
            } 
        }
        // Console.WriteLine ( "end   = " + end.ToString() );
        attribute = Double.Parse ( new string (expr, start, end - start) );
        start = end;
    } else {
        token = (short)  expr [start];
        switch ( (char) token ) {
            case '+' :
            case '-' :
            case '*' :
            case '/' :
                attribute = token;
                break; 
        }                               // do not need the other operators
        ++start;
    }

    return  token;
}

};
