{
#include <stdio.h>

typedef struct My_Sym {
  float value;
} My_Sym;
#define D_UserSym My_Sym

typedef struct My_ParseNode {
  float value;
  struct D_Scope *scope;
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
       expr '+' expr  $left 10   { $$.value = $0.value + $2.value; } 
    |  expr '-' expr  $left 10   { $$.value = $0.value - $2.value; } 
    |  expr '*' expr  $left 20   { $$.value = $0.value * $2.value; }
    |  expr '/' expr  $left 20   { $$.value = $0.value / $2.value; }
    |   '(' expr ')'  $left 30   { $$.value = $1.value; }
    |  identifier '=' expr  $right 0
         {     
           D_Sym *s;
           s = find_D_Sym(${scope}, $n0.start_loc.s, $n0.end);
           if (s==NULL) 
             s = NEW_D_SYM(${scope}, $n0.start_loc.s, $n0.end);
           s->user.value = $2.value;
           $$.value = s->user.value;
         }
    |  identifier
         {  
            D_Sym *s = find_D_Sym(${scope}, $n0.start_loc.s, $n0.end);
            if (s) $$.value = s->user.value;
         }
    |  real  { $$.value = atof($n0.start_loc.s); } 
;

real :  "-?[0-9]+(.[0-9]+)?" 
;

identifier :  "[a-zA-Z_][a-zA-Z_0-9]*"
;
