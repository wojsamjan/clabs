
using System ;

class Calc {

public static void Main ( string[] args )
{
    Console.WriteLine ("Desk Calculator: operators are *, /, +, -, ^, () \n");
    if ( args.Length != 1 ) {
        Console.WriteLine ( "Usage:  calc  expression\n" );
        return; 
    } 

    ClcLog      log = new ClcLog ();
    ClcToken    scanner = new ClcToken ( args[0], log );
    ClcError    error = new ClcError ( scanner, log );
    ClcAction   action = new ClcAction ( scanner, log );

    ClcParser.parse  ( 0, action, scanner, error, log, (short) 0 );

    Console.WriteLine ( "Answer = " + action.get_answer().ToString() );
}

}; 
