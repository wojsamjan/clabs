#include <stdio.h>
#include "css21.h"

extern int yylex();
extern FILE *yyin;
extern char *yytext;
extern int yyleng;

char *tokens[] = {
  "blanks",
  "cdo",
  "cdc",
  "includes",
  "dashmatch",
  "lbrace",
  "plus",
  "greater",
  "comma",
  "string",
  "invalid",
  "ident",
  "hash",
  "import",
  "page",
  "media",
  "charset",
  "important",
  "ems",
  "exs",
  "length",
  "angle",
  "time",
  "freq",
  "dimension",
  "percentage",
  "number",
  "uri",
  "function",
  "comment",
  "id"
};

#define token(n) n>255 ? tokens[n-256] : yytext

int main(int argc, char *argv[]) {
  int kind;

  if (argc == 2) {
    yyin = fopen(argv[1], "r");
  } else {
    yyin = stdin;
  }
  while ((kind = yylex())) {
    if (kind == BLANKS || kind == LBRACE || kind == INCLUDES ||
        kind == DASHMATCH || kind == PLUS || kind == GREATER ||
        kind == COMMA ||
        kind < 256)
      printf("%s", yytext);
    else
      printf("<span class=\"%s\">%s</span>", token(kind), yytext);
  }

  return 0;
}
