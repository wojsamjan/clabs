
class Calc {

public static void main ( String[] args )
{
    System.out.println ("Desk Calculator: operators are *, /, +, -, ^, () \n");
    if ( args.length != 1 ) {
        System.out.println ( "Usage:  calc  expression\n" );
        return; 
    } 

    ClcLog      log = new ClcLog ();
    ClcToken    scanner = new ClcToken ( args[0], log );
    ClcError    error = new ClcError ( scanner, log );
    ClcAction   action = new ClcAction ( scanner, log );

    ClcParser.parse  ( 0, action, scanner, error, log, (short) 0 );

    System.out.println ( "Answer = " +
                          String.valueOf ( action.get_answer() ) );
}

}; 
