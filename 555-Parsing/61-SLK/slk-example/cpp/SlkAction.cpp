/******************************************************************************

    SlkAction.cpp

******************************************************************************/

#include "calc.h"

// -----------------------------------------------------------------------
// Semantic stack action code
// -----------------------------------------------------------------------

void
SlkAction ::
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

node_t *
SlkAction ::
make_node ( double   item,
            node_t  *left,
            node_t  *right )
{
    register
    node_t    *node;

    node = (node_t *)  malloc ( sizeof ( node_t ) );
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
SlkAction ::
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

void 
SlkAction ::
Add ( void )
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

void 
SlkAction ::
Finish ( void )
{
    Answer = pop ( Semantic_stack );

    Tree = pop ( Node_stack );
}

void 
SlkAction ::
Multiply ( void )
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

void 
SlkAction ::
Exponent ( void )
{
    Answer = pop ( Semantic_stack );
    Answer = pow ( pop ( Semantic_stack ), (int) Answer );
    push ( Answer, Semantic_stack );

    Tree = make_node ( '^', NULL, NULL );
    Tree->right = pop ( Node_stack );
    Tree->left = pop ( Node_stack );
    push ( Tree, Node_stack );
}

void 
SlkAction ::
Negate ( void )
{
    Answer = pop ( Semantic_stack );
    push ( -Answer, Semantic_stack );

    Tree = make_node ( '-', NULL, NULL );
    Tree->left = pop ( Node_stack );
    push ( Tree, Node_stack );
}

void
SlkAction ::
Push ( void )
{
    push ( scanner->get_Attribute(), Semantic_stack );

    Tree = make_node ( scanner->get_Attribute(), NULL, NULL );
    push ( Tree, Node_stack );
}

SlkAction ::
SlkAction ( SlkToken   &scanner,
            SlkLog     &log )
{              
    SlkAction::scanner = &scanner;
    SlkAction::log = &log;
    Semantic_stack.top = Semantic_stack.start + STACKSIZE;
    *Semantic_stack.top = 0;
    Node_stack.top = Node_stack.start + STACKSIZE;
    *Node_stack.top = 0;
    Answer = 0;
    Tree = NULL;

    SlkAction::initialize_table();
}

