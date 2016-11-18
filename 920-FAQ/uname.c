/* Plik: uname.c
 * -------------
 * Funkcja uname
 *
 * Wersja z dnia: 16.X.1999
 */

#include <stdio.h>
#include <sys/utsname.h>  /* 'uname' declaration */

int main() {
  struct utsname uname_pointer;
  uname(&uname_pointer);
  printf("System name - %s \n", uname_pointer.sysname);
  printf("Nodename    - %s \n", uname_pointer.nodename);
  printf("Release     - %s \n", uname_pointer.release);
  printf("Version     - %s \n", uname_pointer.version);
  printf("Machine     - %s \n", uname_pointer.machine);
  return 0;
}

/******************************************************
 * Possible results:
 *
 * system name - Linux 
 * Nodename    - *** 
 * Release     - 2.4.0-test11 
 * Version     - #6 Tue Dec 12:00:00 CET 2000
 * Machine     - i486
 *
 *******************************************************/
