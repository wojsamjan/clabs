/* File: popen.c
 * Purpose: Program to demonstrate the popen function.
 * ToDo: Check that the 'popen' was successfull.
 */

#include <stdio.h>

int main() {
  FILE *fp;
  char line[130]; /* line of data from unix command */
  fp = popen("ls -l", "r"); /* issue the command */
  /* read a line */
  while ( fgets( line, sizeof line, fp)) 
    printf("%s", line);
  pclose(fp);
  return 0;
}
