%{
/* W�odek Bzyl <matwb@univ.gda.pl>,       14 lutego 1999.
 ********************************************************
 * Wy�uskiwacz poprawnych s�ow z pliku generowanego przez
 * program `sam32' z pakietu SAM-96
 * <ftp://ftp.mimuw.edu.pl/polszczyzna>
 */

#include <stdio.h>
#include <ctype.h>

FILE *errout; /* plik gdzie b�d� zapisywane wyrazy o b��dnej pisowni */
%}

err_word      ^[a-z����󶼿]+/%\n"{ }%"
word          ^[a-z����󶼿]+/%\n"{".{2,}"}%"

%%

{err_word}    { fprintf(errout, "%s\n", yytext); }
{word}        { fprintf(stdout, "%s\n", yytext); }
\n|.	      { /* ignoruj reszt� */ ; }

%%
int main (int argc, char *argv[])
{
  if (argc>1) errout=fopen(argv[1],"a");
  else errout=fopen("/dev/null","a");
  if (errout==NULL) errout=stderr;

  yylex();
}
int yywrap() 
{
  return 1;
}
