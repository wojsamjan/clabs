/*
   Przepisz wejście na wyjście – zastępując jednym znakiem odstępu 
   każdy ciąg złożony z jednego lub kilku znaków odstępu lub tabulacji.
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
  int c, state;

  c=getchar();
  state=1;

  while (1) {
    switch (state) {

    case 1: 
      switch (c) {
      case ' ': putchar(' ');
	c=getchar();
	state=2;
	break;
      case '\t': putchar(' ');
	c=getchar(); 
	state=3;
	break;
      case EOF: 
	exit(EXIT_SUCCESS);
      default: putchar(c); 
	c=getchar(); 
	state=1; 
	break;
      }
      break;

    case 2: 
      switch (c) {
      case ' ':
	c=getchar(); 
	state=2;
	break;
      case EOF:
	exit(EXIT_SUCCESS);
      default: putchar(c);
	c=getchar(); 
	state=1; 
	break;
      }
      break;

    case 3:
      switch (c) {
      case '\t':
	c=getchar(); 
	state=3;
	break;
      case EOF:
	exit(EXIT_SUCCESS);
      default: putchar(c);
	c=getchar(); 
	state=1; 
	break;
      }
      break;


    }
  }

  return EXIT_SUCCESS;
}
