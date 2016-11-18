/* File: clrscr.c
 *
 * Purpose: Clear the screen with VT100 escape codes. This can be done
 *          with conio.h on PCs - non standard code. 
 */

#include <stdio.h>

void clrscr(void);

int main() {
  clrscr();
  return 0;
}

void clrscr(void) {
    printf("\033[2J"); /* clear the entire screen */
    printf("\033[0;0f"); /* move cursor to the top left hand corner */
}
