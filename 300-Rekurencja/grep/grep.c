/*
   $Date: 2004/10/08 12:28:40 $
   $Revision: 1.1 $
*/

#include <stdio.h>
#include <string.h>
#include "grep.h"

int match(char *regexp, char *text)
{
  if (regexp[0]=='^')
    return matchhere(regexp+1,text);
  do {
    if (matchhere(regexp,text))
      return 1;
  } while (*text++ != '\0');
  return 0;
}

int matchhere(char *regexp, char *text)
{
  if (regexp[0]=='\0')
    return 1;
  if (regexp[1]=='*')
    return matchstar(regexp[0],regexp+2,text);
  if (regexp[0]=='$' && regexp[1]=='\0')
    return *text=='\0';
  if (*text != '\0' && (regexp[0]=='.' || regexp[0]==*text))
    return matchhere(regexp+1,text+1);
  return 0;
}

int matchstar(int c, char *regexp, char *text)
{
  do {
    if (matchhere(regexp,text))
      return 1;
  } while (*text!='\0' && (*text++==c || c=='.'));
  return 0;
}

int grep(char *regexp, FILE *f, char *name)
{
  int n, nmatch = 0;
  char buf[BUFSIZ]; /* pytanie: gdzie jest zdefiniowane BUFSIZ? */

  while (fgets(buf,sizeof buf,f) != NULL) {
    n=strlen(buf);
    if (n>0 && buf[n-1]=='\n')
      buf[n-1]='\0';
    if (match(regexp,buf)) {
      nmatch++;
      if (name != NULL)
	printf("%s:",name);
      printf("%s\n",buf);
    }
  }
  return nmatch;
}
