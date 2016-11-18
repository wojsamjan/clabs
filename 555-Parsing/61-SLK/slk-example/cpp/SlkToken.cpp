/*****************************************************************************
 
    SlkToken.cpp
  
******************************************************************************/

#include "calc.h"

short 
SlkToken ::
peek ( int   level )                    // scan next token without consuming it
{
    short     token = 0;

    printf ( "peek_token is not called in an LL(1) grammar\n" );

    return  token;
}

SlkToken :: 
SlkToken ( char     *input,
           SlkLog   &log )
         : Scanner ( input, log )
{
}

