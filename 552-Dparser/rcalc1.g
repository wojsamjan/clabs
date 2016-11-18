{
#include <stdio.h>

typedef struct My_ParseNode {
  float value;
} My_ParseNode;
#define D_ParseNode_User My_ParseNode
}

translation_unit : 
  statement*
;
 
statement :
  expr ';' { printf("%f\n", $0.value); }
;

expr :
    |  real  { $$.value = atof($n0.start_loc.s); } 
    |  expr '+' expr  $left 10   { $$.value = $0.value + $2.value; } 
    |  expr '-' expr  $left 10   { $$.value = $0.value - $2.value; } 
    |  expr '*' expr  $left 20   { $$.value = $0.value * $2.value; }
    |  expr '/' expr  $left 20   { $$.value = $0.value / $2.value; }
    |   '(' expr ')'   { $$.value = $1.value; }
;

real: 
  "-?[0-9]+(.[0-9]+)?" 
;
