/**************************************************************************

    SlkError.h

**************************************************************************/

#ifndef _SLKERROR_H
#define _SLKERROR_H

#include "calc.h"

class SlkError
{

public:

    SlkError ( SlkToken &tokens,
               SlkLog   &log );

    short
    mismatch ( short     symbol,
               short     token );
    
    short
    no_entry ( short     nonterminal,
               short     token,
               int       level );
    
    void
    input_left ( void );

private:

    SlkToken *tokens;
    SlkLog   *log;

};

#endif

