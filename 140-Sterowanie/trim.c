/*  $Revision: 1.2 $
    $Date: 2004/11/19 13:18:15 $ 
*/

/* Instrukcje: break, continue */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>  /* biblioteka standardowa: man string */

/* trim:
     usuñ z s koñcowe znaki odstêpu, tabulacji, nowego wiersza
*/
int trim(char s[]);

int main()
{
  char tekst[] = "sierotka ma rysia";
  int len;

  len = strlen(tekst);
  printf("przed trim: `%s' (len = %d)\n", tekst, len); 

  len = trim(tekst);
   
  printf("   po trim: `%s' (len = %d)\n", tekst, len); 
  return EXIT_SUCCESS;
}

int trim(char s[])
{
  int n;

  for (n=strlen(s)-1; n>=0; n--)
    if (s[n]!=' ' && s[n]!='\t' && s[n]!='\n')
      break;
  s[n+1]='\0';
  return n;
}

/* Fragment programu przetwarzaj±cy tylko nieujemne
   elementy tablicy a; elementy ujemne s± pomijane:

   for (i=0; i<n; i++) {
     if (a[i]<0)    // pomiñ ujemny element
       continue;
     <przetwarzaj element nieujemny>
   }
*/
