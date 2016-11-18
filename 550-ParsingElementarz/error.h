/*
    $URL: http://manta.univ.gda.pl/svn/wb/labs/c/550-ParsingElementarz/error.h $
    $Revision: 183 $
    $Date: 2006-11-19 16:29:41 +0100 (nie, 19 lis 2006) $
 */

#ifndef error_included
#define error_included

/* 
 error() generates an error string, expanding % constructions
 appearing in the error message string just as printf does.
 If an error handler exception has been introduced (see the
 "exception.h" facility), the ErrorException exception is
 raised with the expanded error string as argument.  If
 there is no ErrorException defined, the program exits
 with a status code indicating failure (as given by the
 constant ErrorExitStatus). The length of the error
 message string following expansion must not exceed
 MaxErrorMessage, and it is the client's responsibility
 to ensure this.
*/

void error(char *msg, ...);

#endif
