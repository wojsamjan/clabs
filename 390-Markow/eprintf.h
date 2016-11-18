
/*  Program z ksi±¿ki: Brian W. Kernighan i Rob Pike 
  ,,Lekcja Programowania'', WNT 2002  */

/* eprintf: wypisz komunikat o b³êdzie i zakoñcz */
extern	void	eprintf(char *, ...);

/* estrdup: powiek napis, informuj w razie b³êdu */
extern	char   *estrdup(char *);

/* emalloc: funkcja malloc oraz informowanie o b³êdzie */
extern	void   *emalloc(size_t);

/* progname: przeka¿ zapamiêtan± nazwê programu */
extern	char   *progname(void);

/* setprogname: zapamiêtaj nazwê programu */
extern	void	setprogname(char *);

#define	NELEMS(a)  (sizeof(a) / sizeof(a[0]))
