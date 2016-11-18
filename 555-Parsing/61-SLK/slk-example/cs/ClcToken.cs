
using System ; 

class ClcToken : Scanner {

internal
ClcToken ( string   input,
           ClcLog   log )
    : base ( input, log )
{
}

public
short 
peek ( int   level )                    // scan next token without consuming it
{
    short     token = 0;

    Console.WriteLine ( "peek_token is not called in an LL(1) grammar\n" );

    return  token;
}

};
