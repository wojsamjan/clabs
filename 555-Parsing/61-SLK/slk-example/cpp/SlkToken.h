/**************************************************************************

    SlkToken.h

**************************************************************************/

#ifndef _SLKTOKEN_H
#define _SLKTOKEN_H

#include "calc.h"
#include "scanner.h"

class SlkToken : public Scanner
{

public:

    SlkToken ( char     *input,
               SlkLog   &log ); 
    
    short 
    peek ( int   level );
    
};

#endif

