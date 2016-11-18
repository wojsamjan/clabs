/* Example: anatomy of a simple C program. */

/* It's useful to put comments in your programs to explain
what you're doing. Not too few, not too many: one helpful
comment every 10 to 20 lines of code is probably about
right. This program has far too many! */

/* Note: C doesn't allow nested comments: you can't put one
comment inside another! */

#include <stdio.h>
/* This is a preprocessor directive.
Most C programs need to include the standard header file
<stdio.h>, which deals with input and output. For instance,
it declares the function printf, for formatted printing. */

#define ANSWER 42
/* This is another preprocessor directive.
The symbol ANSWER will be replaced by 42. It's useful for
defining constants. */

int a, b;
/* Declared outside any function, these are external
(global) variables, accessible to all functions in this
file. There are good reasons for minimising the use of
globals! */

int mult_and_print(float f, float g);
void add(void);
/* Function prototypes. Their actual definitions follow
main. */

int main() {
  /* This is a function definition. Every C program needs a
  main function, where execution starts. */

  float x, y = 13.7;
  /* Declaring two local variables, visible only within the
  main function */

  x = y * ANSWER + a;  /* This is a statement */

  add();
  b = mult_and_print(x, y);  /* These are function calls */
}


void add(void)  /* Definition of a function */
{
  a = a + b;
  return;
}


int mult_and_print(float f, float g)
/* Definition of a function */
{
  int r;  /* Declaring a local variable */

  r = (int) (f * g);  /* A statement */

  printf("Yesterday I saw %i penguins!\n", r);
  /* A function call; the prototype for printf is in
  <stdio.h> */

  return r;  /* Returning a value to the calling function */
}
