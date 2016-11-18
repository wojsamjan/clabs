
class Scanner {

Scanner ( String  input,
          ClcLog  log )
{
    this.log = log;
    expr = input.toCharArray();
    length = expr.length;
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

    while ( start < length  &&  Character.isWhitespace ( expr [start] ) ) {
        ++start;
    }                       
    last_attribute = attribute; 
                        
    if ( start >= length ) {
        token = ClcConstants.END_OF_SLK_INPUT_;
    } else if ( Character.isDigit ( expr [start] )  ||  expr [start] == '.' ) {
        token = ClcConstants.NUMBER_;
        end = start;
        while ( Character.isDigit ( expr [end] )  ||  expr [end] == '.' ) {
            ++end;
            if ( end == length ) {
                break; 
            } 
        }
        // System.out.println ( "end   = " + String.valueOf ( end   ));
        attribute = Double.valueOf 
                    ( new String (expr, start, end - start) ).doubleValue();
        start = end;
    } else {
        token = (short)  expr [start];
        switch ( token ) {
            case '+' :
            case '-' :
            case '*' :
            case '/' :
                attribute = token;
        }                               // do not need the other operators
        ++start;
    }

    return  token;
}

};
