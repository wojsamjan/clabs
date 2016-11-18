/*****************************************************************************

    SlkLog.h

******************************************************************************/

#ifndef _SLKLOG_H
#define _SLKLOG_H

class SlkLog
{

public:

    void trace ( char  *message );
    void trace_depth ( char  *message, int    depth );
    void trace_production ( int  production_number );
    void trace_action ( int  action_number );
};

#endif

