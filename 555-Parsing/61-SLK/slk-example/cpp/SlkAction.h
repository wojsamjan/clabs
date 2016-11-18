/*************************************************************************

    SlkAction.h

*************************************************************************/

#ifndef _SLKACTION_H
#define _SLKACTION_H

#include "calc.h"

#define STACKSIZE   511

#define push(n,s) if (s.top > s.start) { *--s.top = n; }\
        else { puts ("Calc: stack overflow"); exit(1); }

#define pop(s)   ( *s.top++ )

typedef struct _stack
{   double   *top ,
              start [STACKSIZE + 1];
} stack;

typedef struct _node { double   item;
                       struct
                      _node    *left,
                               *right;
} node_t;

typedef struct _stack2
{   node_t  **top ,
             *start [STACKSIZE + 1];
} stack2;


class SlkAction
{

public:

    SlkAction ( SlkToken   &scanner,
                SlkLog     &log );

    #include "SlkTable.h"

    double      get_Answer ( void )          { return  Answer; }
    node_t     *get_Tree ( void )            { return  Tree; }
    double      post_order ( node_t  *tree );

private:

    SlkToken   *scanner;
    SlkLog     *log;
    stack       Semantic_stack;
    double      Answer;
    node_t     *Tree;
    stack2      Node_stack;

    void dump_stack ( stack   s );
    node_t * make_node ( double   item, node_t  *left, node_t  *right );

};

#endif

