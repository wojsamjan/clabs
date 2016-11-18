/*****************************************************************************

    scanner.cpp
    
******************************************************************************/

#include "calc.h"

short 
Scanner::
get ( void )
{
    short    token;

    while ( isspace ( *Scan_text ) ) {
        ++Scan_text;
    }
    Last_attribute = Attribute; 

    if ( ! *Scan_text ) {
        token = END_OF_SLK_INPUT_;
    } else if ( isdigit ( *Scan_text )  ||  *Scan_text == '.' ) {
        token = NUMBER_;
        Attribute = atof ( Scan_text );
        while ( isdigit ( *Scan_text )  ||  *Scan_text == '.' ) {
            ++Scan_text;
        }
    } else {
        token = *Scan_text;
        switch ( token ) {
            case '+' :
            case '-' :
            case '*' :
            case '/' :
                Attribute = token;
        }                               // do not need the other operators
        ++Scan_text;
    }

    return  token;
}

Scanner ::
Scanner ( char    *input,
          SlkLog  &log )
{
    Scanner::log = &log;

    strncpy ( Expression, input, sizeof ( Expression ) );
    Scan_text = Expression;
}

