
#ifndef TABLE_INCLUDED
#define TABLE_INCLUDED
#define T Table_T

/* Przekazanie `null T' lub `null key' jakiejkolwiek funkcji 
   jest SBW (Sprawdzanym Błędem Wykonania Programu) */

typedef struct T *T;

/* Utwórz, zainicjalizuj i zwróć pusty hasz, w którym można przechować
   dowolną liczbę par `key=>value'. `hint' jest szacowaną liczbą par,
   która zostanie umieszczona w haszu. Jest SBW jeśli `hint<0'.
   Funkcja `cmp' porównuje klucze, a `hash' jest funkcją haszującą
   klucze. Dla kluczy `x' i `y' funkcja `cmp' musi zwrócić liczbę 
   całkowitą `<0' lub `=0' lub `>0', w zależności od tego czy 
   `x<y' lub `x=y' lub `x>y'. Jeśli `cmp(x,y)=0', to musi zachodzić 
   równość `hash(x)=hash(y)'. Jeśli `cmp=NULL' lub `hash=NULL', to
   `Table_new' zastosuje funkcje odpowiednie dla kluczy typu `Atom_T'. */

extern T Table_new(int hint, int cmp(const void *x, const void *y),
		   unsigned hash(const void *key));

/* Zwalnia i czyści pamięć zajętą przez `*table'. Jest SBW jeśli
   `table' lub `*table' jest null. */

extern void Table_free(T *table);

/* Zwraca liczbę elementów `key=>value' przechowywanych w `table'. */

extern int Table_length(T table);

/* Zmień wartość powiązaną z `key' w `table' i zwróć poprzednią wartość.
   Jeśli `table' nie zawiera `key', to dodaj `key=>value' do `table'
   i zwróć NULL. */

extern void *Table_put(T table, const void *key,
		       void *value);

/* Zwraca wartość powiązaną z `key' w `table' lub null jeśli `table'
   nie zawiera `key'. */ 

extern void *Table_get(T table, const void *key);

/* Usuń parę `key=>value' z `table' i zwróć usuniętą `value'.
   Jeśli `table' nie zawiera `key', `Table_remove' nie zmienia hasza
   i zwraca NULL. */

extern void *Table_remove(T table, const void *key);

/* Wywołaj `apply(key,&value,cl) dla każdej pary `key=>value' w haszu 
   `table'. Jest SBW jeśli `apply' zmienia `table'. */

extern void Table_map(T table,
		      void apply(const void *key, void **value, void *cl),
		      void *cl);

/* Utwórz tablicę o 2N+1 elementach zawierającą N par `(key,value)'.
   i zwróć wskaźnik do pierwszego elementu tablicy. Klucze zostają 
   umieszczone pod parzystymi indeksami, 
   a wartości pod nieparzystymi indeksami.
   Elementem umieszczonym pod indeksem 2N jest `end'. */

extern void **Table_toArray(T table, void *end);

#undef T
#endif
