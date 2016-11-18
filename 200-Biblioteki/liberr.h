#ifndef LIBERR_H
#define LIBERR_H

/*
   Prosta biblioteka obsługi błędów z
     R. Stevens. Advanced Programming in the UNIX Environment
*/

#include <stdarg.h>

#define MAXLINELEN 4096

/* err_ret: wypisz komunikat o błędzie na stderr
            i powróć do procesu wywołującego */
void err_ret(const char *fmt, ...);

/* err_quit: wypisz komunikat o błędzie na stderr
            i zakończ działanie programu */
void err_quit(const char *fmt, ...);

/* log_ret: zapisz komunikat o błędzie do logfile
            i powróć do procesu wywołującego */
void log_ret(char *logfile, const char *fmt, ...);

/* err_quit: zapisz komunikat o błędzie do logfile
            i zakończ działanie programu */
void log_quit(char *logfile, const char *fmt, ...);

#endif
