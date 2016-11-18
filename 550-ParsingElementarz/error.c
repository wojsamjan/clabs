/*
    $URL: http://manta.univ.gda.pl/svn/wb/labs/c/550-ParsingElementarz/error.c $
    $Revision: 183 $
    $Date: 2006-11-19 16:29:41 +0100 (nie, 19 lis 2006) $
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#include "error.h"

/*
    ErrorExitStatus -- Status value used in exit call
    MaxErrorMessage -- Longest error message allowed
 */

#define ErrorExitStatus 1
#define MaxErrorMessage 500

/*
   Writing the Error function requires some care, since it is
   called in circumstances in which parts of the system may be
   broken. 
   The error string should be allocated dynamically,
   so that this function can be used in reentrant code.
   Note that it is critical to exit if the length bound for
   an error message is exceeded, since this error almost
   certainly corrupts the stack.
*/

void error(char *msg, ...)
{
    va_list args;
    char errbuf[MaxErrorMessage + 1];
    char *errmsg;
    int errlen;

    va_start(args, msg);
    vsprintf(errbuf, msg, args);
    va_end(args);
    errlen = strlen(errbuf);
    if (errlen > MaxErrorMessage) {
        fprintf(stderr, "Error: Error Message too long\n");
        exit(ErrorExitStatus);
    }
    errmsg = malloc(errlen + 1);
    if (errmsg == NULL) {
        errmsg = "No memory available";
    } else {
        strcpy(errmsg, errbuf);
    }
    fprintf(stderr, "Error: %s\n", errmsg);
    exit(ErrorExitStatus);
}
