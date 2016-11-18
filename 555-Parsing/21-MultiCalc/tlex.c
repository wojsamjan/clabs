#include <stdio.h>
#include <stdlib.h>

void input_init(void);
int yylex(void);
extern double yylval;

#define VAR 300
#define NUM 400

main () {
  int type;
  int ntokens=0;
  input_init();
  while ((type=yylex())!=0) {
    if (ntokens==10) {
      printf("\n"); 
      ntokens=0;
    } else ntokens++;
  }
  printf("\n");
}
