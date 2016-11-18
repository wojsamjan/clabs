#include <stdio.h>
#include <stdlib.h>

/* squeeze: usuń wszystkie znaki `c' z `s' */
void squeeze(char s[], int c) {
  int i, j;
  for (i=j=0; s[i]!='\0'; i++)
    if (s[i]!=c)
      s[j++]=s[i];
  s[j]='\0';
}

int main() {
  char msg[]="axxbxc";
  int c='x';
  printf("usuń wszystkie znaki `%c' z `%s'\n",c,msg);
  squeeze(msg,c);
  printf("`%s'\n\tok, zrobione\n",msg);
  return EXIT_SUCCESS;
}
