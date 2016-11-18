/*
    BUGS:
     ta wersja usuwa komentarze w napisach, na przykład
     "/\gwiazdka takie jak ten \gwiazdka/"

    Implementacja prostego DFA (deterministycznego automatu skończonego)
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  int c, state;

  c = getchar();
  state = 1;

  while (1) {
    switch (state) {

    case 1:
      switch (c) {
      case '/':
        c = getchar();
        state = 2;
        break;
      case EOF:
        exit(EXIT_SUCCESS);
      default: putchar(c);
        c = getchar();
        state = 1;
        break;
      }
      break;

    case 2:
      switch (c) {
      case '*':
        c = getchar();
        state = 3;
        break;
      case EOF: putchar('/');
        exit(EXIT_SUCCESS);
      default: putchar('/'); putchar(c);
        c = getchar();
        state = 1;
        break;
      }
      break;

    case 3:
      switch (c) {
      case '*':
        c = getchar();
        state = 4;
        break;
      case EOF:
        exit(11);  /* EOF in comment */
      default:
        c = getchar();
        state = 3;
        break;
      }
      break;

    case 4:
      switch (c) {
      case '/':
        c = getchar();
        state = 1;
        break;
      case '*':
        c = getchar();
        state = 4;
        break;
      case EOF:
        exit(11);  /* EOF in comment */
      default:
        c = getchar();
        state = 3;
        break;
      }
      break;

    }
  }

}
