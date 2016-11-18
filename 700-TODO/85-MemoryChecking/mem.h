
#ifndef MEM_INCLUDED
#define MEM_INCLUDED
#include "except.h"

/* Przekazanie `nbytes<=0' jakiejkolwiek funkcji 
   jest SBW (Sprawdzanym B³êdem Wykonania Programu) */

extern const Except_T Mem_Failed;

/* Przydziel `nbytes' bajtów pamiêci i zwróæ wska¼nik do 
   pierwszego bajtu. Pamiêæ nie jest inicjalizowana. 
   Je¶li `Mem_alloc' zg³osi wyj±tek, to `file' i `line'
   informuj± o~miejscu b³êdu. */
extern void *Mem_alloc (long nbytes,
	const char *file, int line);

/* Przydziel pamiêæ na tablicê o `count' elementach, z których ka¿dy
   zajmuje `nbytes' bajtów, i zwróæ wska¼nik do pierwszego bajtu. Jest
   SBW je¶li `count<=0'. Przydzielona pamiêæ jest zerowana, co
   niekoniecznie musi oznaczaæ inicjalizacji wska¼nikami zerowymi
   lub liczbami rzeczywistymi 0.0. Je¶li `Mem_calloc' zg³osi wyj±tek, to
   `file' i `line' informuj± o~miejscu b³êdu. */
 extern void *Mem_calloc(long count, long nbytes,
	const char *file, int line);

/* Je¶li `ptr<>NULL', to zwolnij pamiêæ. Jest NBW je¶li 
   blok pamiêci zaczynaj±cy siê w `ptr' nie zosta³ przydzielony 
   przez uprzednie wywo³anie `Mem_alloc' lub `Mem_calloc'.
   Implementacja mo¿e skorzystaæ z `file' i `line' informuj±c 
   o b³êdach w wykorzystaniu pamiêci. */
extern void Mem_free(void *ptr,
	const char *file, int line);

/* Zmieñ rozmiar bloku pamiêci zaczynaj±cej siê od `ptr'
   i zwróæ wska¼nik do pierwszego bajtu nowego bloku.
   Je¶li `nbytes' jest wiêksze od rozmiaru poprzedniego
   bloku pamiêci, to dodatkowe bajty s± niezainicjalizowane.
   Je¶li `Mem_resize' zg³osi wyj±tek `Mem_failed', to `file'
   i `line' informuj± o miejscu b³êdu. Jest SBW je¶li `ptr==Null'
   i NBW je¶li blok pamiêci zaczynaj±cy siê w `ptr' nie zosta³
   przydzielony przez uprzednie wywo³anie `Mem_alloc' 
   lub `Mem_calloc'. */
extern void *Mem_resize(void *ptr, long nbytes,
	const char *file, int line);

/* Przydziel `nbytes' i zwróæ wska¿nik do pierwszego bajtu. 
   Przydzielone bajty nie s± inicjalizowane. */
#define ALLOC(nbytes) \
	Mem_alloc((nbytes), __FILE__, __LINE__)

/* Przydziel pamiêæ na tablicê rozmiaru `count', której ka¿dy 
   element zajmuje `nbytes' bajtów. Jest SBW je¶li `count<=0'. 
   Przydzielona pamiêæ jest wyzerowana. */
#define CALLOC(count, nbytes) \
	Mem_calloc((count), (nbytes), __FILE__, __LINE__)

/* Zwróæ blok pamiêci dostatecznie du¿y aby pomie¶ciæ `*p',
   wstaw do `p' adrese pocz±tku bloku i zwróæ ten adres.
   NEW0 zeruje przydzielon± pamiêæ, a NEW tego nie robi. 
   Oba makra wyliczaj± `p' dok³adnie raz. */
#define  NEW(p) ((p) = ALLOC((long)sizeof *(p)))
#define NEW0(p) ((p) = CALLOC(1, (long)sizeof *(p)))

/* Je¶li `ptr<>NULL', to zwolnij pamiêæ i~wyzeruj `ptr'. 
   Wska¼nik `ptr' jest wyliczany wiêcej ni¿ raz. */ 
#define FREE(ptr) ((void)(Mem_free((ptr), \
	__FILE__, __LINE__), (ptr) = 0))

/* Zmieñ rozmiar bloku pamiêci zaczynaj±cej od `ptr' do `nbytes'
   i zmieñ `ptr' tak aby wskazywa³a na jej pocz±tek. Wska¼nik
   `p' jest wyliczany wiecej ni¿ raz. */
#define RESIZE(ptr, nbytes) 	((ptr) = Mem_resize((ptr), \
	(nbytes), __FILE__, __LINE__))

#endif
