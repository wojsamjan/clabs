
#ifndef LIST_INCLUDED
#define LIST_INCLUDED
#define T List_T

typedef struct T *T;
struct T {
	T rest;
	void *first;
};

/* UWAGA: Wskaźnik null T dla argumentu `list' 
          jest interpretowany jako lista pusta. */

/* Dopisz `tail' do `list' i zwróć `list'. Jeśli list=null, zwróć `tail'. */
extern T      List_append (T list, T tail);

/* Utwórz i zwróć kopię `list'. */
extern T      List_copy   (T list);

/* Utwórz i zwróć listę, o elementach ``...'' aż do
   napotkania pierwszego wskaźnika null. */
extern T      List_list   (void *x, ...);

/* Przypisz `list->first' do `*x'. Jeśli `x' nie jest równe null
   zwolnij pamięć zajętą przez `list' i zwróć `list->rest'.
   W przypadku list==nul, zwróć null i nie zmieniaj `*x'. */
extern T      List_pop    (T list, void **x);

/* Dopisz nowy węzeł zawierający `x' do początku `list' 
   i zwróć nowo utworzoną listę. */
extern T      List_push   (T list, void *x);

/* Odwróć w miejscu kolejność elementów na `list' i zwróć
   nowo utworzoną listę. */
extern T      List_reverse(T list);

/* Zwróć liczbę elementów `list'. */
extern int    List_length (T list);

/* Zwolnij pamięć i wyzeruj `*list'. 
   Jest SBW (Sprawdzanym Błędem Wykonania Programu, 
   ang. CRE -- Checked Runtime Error) jeśli list==null. */
extern void   List_free(T *list);

/* Wywołaj `apply(&p->first,cl)' dla każdego węzła p `list'.
   Jest NBW (Niesprawdzanym Błędem Wykonania Programu,
   ang. URE -- Unchecked Runtime Error), jeśli `apply'
   zmienia węzły `list'. */
extern void   List_map(T list,
		       void apply(void **x, void *cl), void *cl);

/* Utwórz tablicę o N+1 elementach z pierwszych N elementów
   `list' i zwróć wskaźnik na pierwszy element tablicy.
    Wstaw jako N-ty element `end' do tablicy. */
extern void **List_toArray(T list, void *end);

#undef T
#endif
