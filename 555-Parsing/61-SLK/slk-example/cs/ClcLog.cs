
using System ;

class ClcLog {

public
void
trace ( string  message )
{
    Console.WriteLine ( message );
}

public
void
trace_depth ( string message,
              int    depth )
{
    int     i;

    for ( i = 0;  i < depth;  ++i ) {
        Console.WriteLine ( "    " );
    }
    Console.WriteLine ( message );
}

public
void
trace_production ( short  production_number )
{
    Console.WriteLine ( ClcString.GetProductionName ( production_number ) );
    Console.WriteLine ( "\n" );
}

public
void
trace_action ( short  action_number )
{
    Console.WriteLine ( "\n" );
    Console.WriteLine ( ClcString.GetSymbolName ( action_number ) );
    Console.WriteLine ( "\n\n" );
}

};
