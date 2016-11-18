/*********
#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
#include &lt;ctype.h&gt;
#include &lt;math.h&gt;
#include "SlkParse.h"
#include "SlkTable.h"
#include "SlkString.h"
*********/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "math.h"
#include "SlkParse.h"
#include "SlkTable.h"
#include "SlkString.h"

// -----------------------------------------------------------------------
// Token peeking, scanning
// -----------------------------------------------------------------------

char    Expression [ 512 ],
       *Scan_text;
double  Attribute;
double  Last_attribute;   

short
get_token ( void )
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

short
peek_token ( int   level )              // scan next token without consuming it
{
    short     token = 0;

    printf ( "peek_token is not called in an LL(1) grammar\n" );

    return  token;
}

void
init_peeker ( char    *string )
{
    strncpy ( Expression, string, sizeof ( Expression ) );
    Scan_text = Expression;
}

// -----------------------------------------------------------------------
// Semantic stack action code
// -----------------------------------------------------------------------

#define STACKSIZE   511

#define push(n,s) if (s.top > s.start) { *--s.top = n; }\
        else { puts ("Calc: stack overflow"); exit(1); }

#define pop(s)   ( *s.top ? *s.top++ : 0 )


typedef struct _stack
{   double   *top ,
              start [STACKSIZE + 1];
} stack;

stack    Semantic_stack = { Semantic_stack.start + STACKSIZE };

double   Answer;

void
dump_stack ( stack   s )                        // debugging
{
    double   *top;

    for ( top = s.top;  *top;  ++top ) {
        printf ( "%f ", *top );
    }
    putchar ( '\n' );
}

// <a name="abstract_syntax_tree"></a>
// -----------------------------------------------------------------------
// abstract syntax tree action code
// -----------------------------------------------------------------------

typedef struct _node { double   item;
                       struct
                      _node    *left,
                               *right;
} node_t;

node_t  *Tree;

typedef struct _stack2
{   node_t  **top ,
             *start [STACKSIZE + 1];
} stack2;

stack2   Node_stack = { Node_stack.start + STACKSIZE };

node_t *
make_node ( double   item,
            node_t  *left,
            node_t  *right )
{
    register
    node_t    *node;

    node = malloc ( sizeof ( node_t ) );
    if ( node == NULL ) {
        puts ( "malloc failed\n" );
        exit (1);
    }
    node->item = item;
    node->left = left;
    node->right = right;

    return ( node );
}

double
post_order ( node_t  *tree )
{
    double  left,
            right,
            value;

    if ( tree == NULL ) {
        return  0;
    }
    left = post_order ( tree->left );
    right = post_order ( tree->right );
    switch ( (int) tree->item ) {
        case '-' :
            if ( right ) {
                value = left - right;
            } else {
                value = -left;
            }
            printf ( " %c ", (char) tree->item );
            break;
        case '+' :
            value = left + right;
            printf ( " %c ", (char) tree->item );
            break;
        case '/' :
            value = left / right;
            printf ( " %c ", (char) tree->item );
            break;
        case '*' :
            value = left * right;
            printf ( " %c ", (char) tree->item );
            break;
        case '^' :
            value = pow ( left, (int) right );
            printf ( " %c ", (char) tree->item );
            break;
        default :
            value = tree->item ;
            printf ( " %.2f ", tree->item );
    }

    return  value;
}

// -----------------------------------------------------------------------
// grammar action code functions
//
// Duplicate action methods are illustrated. The first part of each action
// function computes the answer directly. The second part builds an
// abstract syntax tree to be processed later in main.
// -----------------------------------------------------------------------

void Add ( void )
{
    double   op;
    node_t  *node;

    Answer = pop ( Semantic_stack );                        // direct action
    op = pop ( Semantic_stack );
    if ( op == '+' ) {
        Answer = pop ( Semantic_stack ) + Answer;
    } else {
        Answer = pop ( Semantic_stack ) - Answer;
    }
    push ( Answer, Semantic_stack );

    node = pop ( Node_stack );                          // abstract syntax tree
    Tree = pop ( Node_stack );
    Tree->left = pop ( Node_stack );
    Tree->right = node;
    push ( Tree, Node_stack );
}

void Finish ( void )
{
    Answer = pop ( Semantic_stack );

    Tree = pop ( Node_stack );
}

void Multiply ( void )
{
    double   op;
    node_t  *node;

    Answer = pop ( Semantic_stack );
    op = pop ( Semantic_stack );
    if ( op == '*' ) {
        Answer = pop ( Semantic_stack ) * Answer;
    } else {
        Answer = pop ( Semantic_stack ) / Answer;
    }
    push ( Answer, Semantic_stack );

    node = pop ( Node_stack );
    Tree = pop ( Node_stack );
    Tree->left = pop ( Node_stack );
    Tree->right = node;
    push ( Tree, Node_stack );
}

void Exponent ( void )
{
    Answer = pop ( Semantic_stack );
    Answer = pow ( pop ( Semantic_stack ), (int) Answer );
    push ( Answer, Semantic_stack );

    Tree = make_node ( '^', NULL, NULL );
    Tree->right = pop ( Node_stack );
    Tree->left = pop ( Node_stack );
    push ( Tree, Node_stack );
}

void Negate ( void )
{
    Answer = pop ( Semantic_stack );
    push ( -Answer, Semantic_stack );

    Tree = make_node ( '-', NULL, NULL );
    Tree->left = pop ( Node_stack );
    push ( Tree, Node_stack );
}

void Push ( void )
{
    push ( Last_attribute, Semantic_stack );

    Tree = make_node ( Last_attribute, NULL, NULL );
    push ( Tree, Node_stack );
}

void DumpStack ( void )
{
    dump_stack ( Semantic_stack );
}

// -----------------------------------------------------------------------
// parse error routines
// -----------------------------------------------------------------------

#define GET_PRODUCTION_NAME    SlkGetProductionName
#define GET_SYMBOL_NAME        SlkGetSymbolName

short
mismatch ( short     symbol,
           short     token )
{
    printf ( "  expecting '%s' but found '%s' \n", GET_SYMBOL_NAME (symbol),
                                                   GET_SYMBOL_NAME (token) );
    return ( token );
}

short
no_entry ( short     nonterminal,
           short     token,
           int       level )
{
    #ifdef DEBUG
        printf ( "  no entry for nonterminal/token:  %s  %s \n",
                                            GET_SYMBOL_NAME ( nonterminal ),
                                            GET_SYMBOL_NAME (token) );
    #else
        printf ( "  syntax error: skipping input '%s' \n",
                                            GET_SYMBOL_NAME (token) );
    #endif

    token = get_token ();                       // advance the input

    return ( token );
}

void
input_left ( void )
{
}

// -----------------------------------------------------------------------
// parse display routines
// -----------------------------------------------------------------------

void  trace ( char  *message )
{
    fputs ( message, stdout );
}

void trace_depth ( char  *message, int    depth )
{
    int     i;

    for ( i = 0;  i < depth;  ++i ) {
        fputs ( "    ", stdout );
    }
    fputs ( message, stdout );
}

void trace_production ( int  production_number )
{
    fputs ( GET_PRODUCTION_NAME ( production_number ), stdout );
    fputs ( "\n", stdout );
}

void trace_action ( int  action_number )
{
    fputs ( "\n", stdout );
    fputs ( GET_SYMBOL_NAME ( action_number ), stdout );
    fputs ( "\n\n", stdout );
}

// -----------------------------------------------------------------------
// main for desk calculator
// -----------------------------------------------------------------------

#define HELP        1
#define DISPLAY     2
#define CONTINUE    4

main ( int     argc,
       char  **argv )
{
    char      *p,
              *expr = NULL;
    int        options = CONTINUE;
    SlkToken   peeker = { get_token, peek_token };
    SlkError   error = { mismatch, no_entry, input_left };
    SlkLog     log = { trace, trace_depth, trace_production, trace_action };
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
        init_peeker ( expr );
        SlkParse ( options & DISPLAY, SlkActions, peeker, error, log, 0 );
        printf ("Answer = %f\n", Answer);
        printf ("post order abstract syntax tree traversal:\n" );
        Answer = post_order ( Tree );
        printf ("\nAnswer = %f\n", Answer);
    }

    if ( options & CONTINUE ){
        for (;;){
            printf ("Enter expression: ");
            fflush ( stdout );
            p = gets ( scanline );
            if ( p  &&  *p ) {
                init_peeker ( p );
                SlkParse ( options & DISPLAY, SlkActions, peeker, error, log, 0 );
                printf ("Answer = %f\n", Answer);
                printf ("post order abstract syntax tree traversal:\n" );
                Answer = post_order ( Tree );
                printf ("\nAnswer = %f\n", Answer);
            } else {
                break;
            }
	}
    }

    return 0;
}
