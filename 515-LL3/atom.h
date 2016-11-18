
#ifndef ATOM_INCLUDED
#define ATOM_INCLUDED

/* UWAGA: Jest SBW, przekazanie null `str' do każdej funkcji.
          Jest NBW, modyfikacja atomu. */

/* Zwróć długość atomu `str'. Jest SBW, jeśli `str' nie jest atomem. */
extern int Atom_length(const char *str);

/* Zwróć atom dla `str[0,len-1]', tworząc go, jeśli nie zostało to
   jeszcze zrobione. Jest SBW, jeśli len<0. */
extern const char *Atom_new(const char *str, int len);

/* Zwróć atom `Atom_new(str,strlen(str))'. */
extern const char *Atom_string(const char *str);

/* Zwróć atom dla reprezentacji dziesiętnej `n'. */
extern const char *Atom_int(long n);

#endif
