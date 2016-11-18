#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "liberr.h"

static void err_prn(const char *fmt, va_list ap, char *logfile);

void err_ret(const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  err_prn(fmt, ap, NULL);
  va_end(ap);
  return;
}

void err_quit(const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  err_prn(fmt, ap, NULL);
  va_end(ap);
  exit(1);
}

void log_ret(char *logfile, const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  err_prn(fmt, ap, logfile);
  va_end(ap);
  return;
}

void log_quit(char *logfile, const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  err_prn(fmt, ap, logfile);
  va_end(ap);
  exit(1);
}

/* err_prn: wypisz komunikat o błędzie i powróć do procesu wywołującego */

static void err_prn(const char *fmt, va_list ap, char *logfile) {
  int save_err;
  char buf[MAXLINELEN];
  FILE *plf;

  save_err = errno;
  vsprintf(buf, fmt, ap);
  sprintf(buf+strlen(buf), ": %s\n", strerror(save_err));
  fflush(stdout);  /* jeśli stdout == stderr */

  if (logfile != NULL) {
    if ((plf = fopen(logfile, "a")) != NULL) {
      fputs(buf, plf);
      fclose(plf);
    } else {
      fputs("nie udało się otworzyć pliku dziennika\n", stderr);
    }
  } else {
    fputs(buf, stderr);
  }

  fflush(NULL);  /* wymieć wszystko */
  return;
}
