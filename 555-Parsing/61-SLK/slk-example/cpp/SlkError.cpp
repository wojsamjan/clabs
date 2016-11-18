/*****************************************************************************
 
    SlkError.cpp
  
******************************************************************************/

#include "calc.h"

#define GET_SYMBOL_NAME        SlkGetSymbolName

short
SlkError ::
mismatch ( short     terminal,
           short     token )
{
    printf ( "  expecting '%s' but found '%s' \n", GET_SYMBOL_NAME ( terminal ),
                                                   GET_SYMBOL_NAME ( token ) );

    return  token;
}

short
SlkError ::
no_entry ( short     nonterminal,
           short     token,
           int       level )
{
    #ifdef DEBUG
        printf ( "  no entry for nonterminal/token:  %s  %s \n",
                                            GET_SYMBOL_NAME ( nonterminal ),
                                            GET_SYMBOL_NAME ( token ) );
    #else
        printf ( "  syntax error: skipping input '%s' \n",
                                            GET_SYMBOL_NAME ( token ) );
    #endif

    token = tokens->get ();                       // advance the input

    return  token;
}

void
SlkError ::
input_left ( void )
{
}

SlkError ::
SlkError ( SlkToken &tokens,
           SlkLog   &log )
{
    SlkError::log = &log;
    SlkError::tokens = &tokens;
}

