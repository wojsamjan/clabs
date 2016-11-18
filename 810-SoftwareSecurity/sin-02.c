/*
    2.  problemtyczne formatowanie napisów (format string problems)
*/

#include <stdio.h>

int main(int argc, char* argv[])
{
  if(argc > 1)
    printf(argv[1]);
  return 0;
}

/*
   $ sin-02 "hello world"    # ok
   $ sin-02 "%x %x"          # ciekawe? [rezultat podobny do => bfc4f080 bfc4efe8]

   One of the least used format specifiers is %n,
   which writes the number of characters that should
   have been written so far into the address of the
   variable you gave as the corresponding argument.

   Przykład (n.c):

     unsigned int bytes;
     printf("%s%n\n", argv[1], &bytes);
     printf("Your input was %d characters long\n, bytes");

   $ sin-02 "%s%n\n"  # haker kontroluje formatkę
   $ sin-02 "%d%n\n"  # --"--

   printf(user_input);         źle    -- użytkownik kontroluje formatkę
   fprintf(STDOUT, err_msg);   źle    -- j.w.
   printf("%s", user_input);   dobrze -- programista kontroluje formatkę
*/
