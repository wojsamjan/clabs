/*****************************************************************************

    SlkLog.cpp
  
******************************************************************************/

#include "calc.h"

#define GET_PRODUCTION_NAME    SlkGetProductionName
#define GET_SYMBOL_NAME        SlkGetSymbolName

void
SlkLog ::
trace ( char  *message )
{
    fputs ( message, stdout );
}

void
SlkLog ::
trace_depth ( char  *message,
              int    depth )
{
    int     i;

    for ( i = 0;  i < depth;  ++i ) {
        fputs ( "    ", stdout );
    }
    fputs ( message, stdout );
}

void
SlkLog ::
trace_production ( int  production_number )
{
    fputs ( GET_PRODUCTION_NAME ( production_number ), stdout );
    fputs ( "\n", stdout );
}

void
SlkLog ::
trace_action ( int  action_number )
{
    fputs ( "\n", stdout );
    fputs ( GET_SYMBOL_NAME ( action_number ), stdout );
    fputs ( "\n\n", stdout );
}

