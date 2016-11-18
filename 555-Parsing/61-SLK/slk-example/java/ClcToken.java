
class ClcToken extends Scanner {

ClcToken ( String   input,
           ClcLog   log )
{
    super ( input, log ); 
}

public
short 
peek ( int   level )                    // scan next token without consuming it
{
    short     token = 0;

    System.out.print ( "peek_token is not called in an LL(1) grammar\n" );

    return  token;
}

};
