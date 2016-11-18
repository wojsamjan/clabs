/*****************************************************************************

    calc.cpp

******************************************************************************/

#include "calc.h"

#define HELP        1
#define DISPLAY     2
#define CONTINUE    4

int 
main ( int     argc,
       char  **argv )
{
    char      *p,
              *expr = NULL;
    int        options = CONTINUE;
    double     answer;
    char       scanline [ 512 ];

    while ( --argc > 0 ) {                      // process command line options
        p = *++argv;
        switch ( *p ) {
            case '-':
                while ( *++p ) {
                    switch ( *p ) {
                        case 'd':
                            options |= DISPLAY;
                            break;
                        case 'h':
                        case '?':
                            options |= HELP;
                            break;
                        default:
                            fprintf (stderr, "Invalid option, %c\n", *p);
                    }
                }
                break;
            default:
                expr = p;
        }
    }
    printf ("DESK CALCULATOR: operators are *, /, +, -, ^  (calc -h for help)\n");
    if (options & HELP){
        printf (
            "Usage:  calc  [expression] [ options ]\n\n"

            "  -d    display parse derivation \n"
            "  -h    help \n"
            "\n"
            );
    }

    if ( expr ) {
        options &= ~CONTINUE;
        SlkLog      log;
        SlkToken    scanner ( expr, log );
        SlkError    error ( scanner, log );
        SlkAction   action ( scanner, log );

        SlkParse ( (options & DISPLAY), action, scanner, error, log, 0 );

        printf ("Answer = %f\n", action.get_Answer() );
        printf ("post order abstract syntax tree traversal:\n" );
        answer = action.post_order ( action.get_Tree() );
        printf ("\nAnswer = %f\n", answer );
    }

    if ( options & CONTINUE ){
        for (;;){
            printf ("Enter expression: ");
            fflush ( stdout );
            p = gets ( scanline );
            if ( p  &&  *p ) {
                SlkLog      log;
                SlkToken    scanner ( scanline, log );
                SlkError    error ( scanner, log );
                SlkAction   action ( scanner, log );
        
                SlkParse ( (options & DISPLAY), action, scanner, error, log, 0 );
        
                printf ("Answer = %f\n", action.get_Answer() );
                printf ("post order abstract syntax tree traversal:\n" );
                answer = action.post_order ( action.get_Tree() );
                printf ("\nAnswer = %f\n", answer );
            } else {
                break;
            }
	}
    }

    return 0;
}

