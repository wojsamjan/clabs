/*
 * This file contains a main program that reports the
 * length of an input line.
 */

#include <stdio.h>
#include "genlib.h"
#include "strlib.h"
#include "simpio.h"

/* Main program */

int main()
{
    string str;

    printf("This program tests the StringLength function.\n");
    printf("Enter a string: ");
    str = GetLine();
    printf("The length is %d.\n", StringLength(str));
    return 0;
}
