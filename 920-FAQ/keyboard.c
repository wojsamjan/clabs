/* File: keyboard.c
 * Purpose: Reset the keyboard from line mode to character mode and
 *          suppress the echo when a key is entered. This allow the
 *          program to get a character without the user pressing ENTER.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* memset */

void SetKeyboard  (void);
void ResetKeyboard(void);

int main() {
  char Characters[1024];
  int Inc=0;
  memset(Characters, 0, 1024);
  printf("Press a load of characters (q=exit)\n");
  SetKeyboard();
  for(Inc = 0; (Characters[Inc] = getchar()) != 'q'; Inc++);
  ResetKeyboard();
  printf("You pressed: %s\n", Characters);
  return 0;
}

/* Set the keyboard. */
void SetKeyboard(void) {
  system("stty raw -echo");
}

/* Return the keyboard to its original state. If this is not called
 * before the program ends, the keyboard will remain in its reconfigured
 * state. */
void ResetKeyboard(void) {
  system("stty -raw echo");
}
