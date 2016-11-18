
/*  Program z ksi±¿ki: Brian W. Kernighan i Rob Pike 
  ,,Lekcja Programowania'', WNT 2002  */

#include <stdio.h>
#include <stdlib.h>
#include "eprintf.h"
#include <stdarg.h>
#include <string.h>
#include <errno.h>

static char *name = NULL;  /* nazwa programu u¿ywana w komunikatach */

void eprintf(char *fmt, ...)
{
	va_list args;

	fflush(stdout);
	if (progname() != NULL)
		fprintf(stderr, "%s: ", progname());

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	if (fmt[0] != '\0' && fmt[strlen(fmt)-1] == ':')
		fprintf(stderr, " %s", strerror(errno));
	fprintf(stderr, "\n");
	exit(2); /* zwyczajowa warto¶æ u¿ywana w wypadku b³êdu wykonania */
}

void *emalloc(size_t n)
{
	void *p;

	p = malloc(n);
	if (p == NULL)
		eprintf("malloc of %u bytes failed:", n);
	return p;
}

char *estrdup(char *s)
{
	char *t;

	t = (char *) malloc(strlen(s)+1);
	if (t == NULL)
		eprintf("estrdup(\"%.20s\") failed:", s);
	strcpy(t, s);
	return t;
}

char *progname(void)
{
	return name;
}

void setprogname(char *str)
{
	name = estrdup(str);
}
