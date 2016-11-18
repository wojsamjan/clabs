%{
/* W³odek Bzyl <matwb@univ.gda.pl>,       14 lutego 1999.
 ********************************************************
 * Wy³uskiwacz poprawnych s³ow z pliku generowanego przez
 * program `sam32' z pakietu SAM-96
 * <ftp://ftp.mimuw.edu.pl/polszczyzna>
 */

#include <stdio.h>
#include <ctype.h>

FILE *errout; /* plik gdzie bêd± zapisywane wyrazy o b³êdnej pisowni */
%}

err_word      ^[a-z±æê³ñó¶¼¿]+/%\n"{ }%"
word          ^[a-z±æê³ñó¶¼¿]+/%\n"{".{2,}"}%"

%%

{err_word}    { fprintf(errout, "%s\n", yytext); }
{word}        { fprintf(stdout, "%s\n", yytext); }
\n|.	      { /* ignoruj resztê */ ; }

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
