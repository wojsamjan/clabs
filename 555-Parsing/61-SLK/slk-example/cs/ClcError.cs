
using System ;

class ClcError {

internal
ClcError ( ClcToken tokens,
           ClcLog   log )
{
    this.log = log;
    this.tokens = tokens;
}

private ClcToken tokens;
private ClcLog   log;

public
short
mismatch ( short     terminal,
           short     token )
{
    Console.WriteLine ( "  expecting " +
                           ClcString.GetSymbolName ( terminal ) +
                         " but found " +
                           ClcString.GetSymbolName ( token ) );

    return  token;
}

public
short
no_entry ( short     nonterminal,
           short     token,
           int       level )
{
    Console.WriteLine ( "  syntax error: skipping input " +
                                          ClcString.GetSymbolName ( token ) );

    token = tokens.get ();                       // advance the input

    return  token;
}

public
void
input_left ()
{
}

};
