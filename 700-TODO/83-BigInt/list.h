
#ifndef LIST_INCLUDED
#define LIST_INCLUDED
#define T List_T

typedef struct T *T;
struct T {
	T rest;
	void *first;
};

/* UWAGA: Wska¼nik null T dla argumentu `list' 
          jest interpretowany jako lista pusta. */

/* Dopisz `tail' do `list' i zwróæ `list'. Je¶li list=null, zwróæ `tail'. */
extern T      List_append (T list, T tail);

/* Utwórz i zwróæ kopiê `list'. */
extern T      List_copy   (T list);

/* Utwórz i zwróæ listê, o elementach ``...'' a¿ do
   napotkania pierwszego wska¼nika null. */
extern T      List_list   (void *x, ...);

/* Przypisz `list->first' do `*x'. Je¶li `x' nie jest równe null
   zwolnij pamiêæ zajêt± przez `list' i zwróæ `list->rest'.
   W przypadku list==nul, zwróæ null i nie zmieniaj `*x'. */
extern T      List_pop    (T list, void **x);

/* Dopisz nowy wêze³ zawieraj±cy `x' do pocz±tku `list' 
   i zwróæ nowo utworzon± listê. */
extern T      List_push   (T list, void *x);

/* Odwróæ w miejscu kolejno¶æ elementów na `list' i zwróæ
   nowo utworzon± listê. */
extern T      List_reverse(T list);

/* Zwróæ liczbê elementów `list'. */
extern int    List_length (T list);

/* Zwolnij pamiêæ i wyzeruj `*list'. 
   Jest SBW (Sprawdzanym B³êdem Wykonania Programu, 
   ang. CRE -- Checked Runtime Error) je¶li list==null. */
extern void   List_free   (T *list);

/* Wywo³aj `apply(&p->first,cl)' dla ka¿dego wêz³a p `list'.
   Jest NBW (Niesprawdzanym B³êdem Wykonania Programu,
   ang. URE -- Unchecked Runtime Error), je¶li `apply'
   zmienia wêz³y `list'. */
extern void   List_map    (T list,
	void apply(void **x, void *cl), void *cl);

/* Utwórz tablicê o N+1 elementach z pierwszych N elementów
   `list' i zwróæ wska¼nik na pierwszy element tablicy.
    Wstaw jako N-ty element `end' do tablicy. */
extern void **List_toArray(T list, void *end);

#undef T
#endif
