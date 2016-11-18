
/* csv2.h: drugi interfejs dla CSV */

#ifndef CSV2_H_INCLUDED
#define CSV2_H_INCLUDED

/*  Funkcja czyta jeden wiersz z otwartego pliku wej¶ciowego f.
    Zwraca wska¼nik do wczytanego wiersza z usuniêtym znakiem `\n' 
    lub zwraca NULL po napotkaniu EOF.
    Wiersz mo¿e byæ dowolnej d³ugo¶ci.  */

extern const char *csv_getline(FILE *f);  /* pobierz kolejny wiersz */

/*  Funkcja zwraca n-te pole wiersza wczytanego przez ostatnie
    wywo³anie csv_getline lub NULL je¶li n<0 albo n jest wiêksze
    od indeksu ostatniego pola.
    Indeksem pierwszego pola jest 0.
    Cudzys³owy otaczaj±ce pole s± usuwane.
    W obrêbie "..." podwójny znak cudzys³owu "" jest zastêpowany
    przez jeden znak " oraz przecinek nie jest separatorem.
    W polach nie otoczonych cudzys³owami, cudzys³ów jest zwyk³ym
    znakiem.
    Pól mo¿e byæ dowolnie wiele i mog± byæ dowolnej d³ugo¶ci.
    Zachowanie funkcji jest nieokre¶lone przed pierwszym
    wywo³aniem funkcji csv_getline.  */

extern const char *csv_field(int n);  /* przeka¿ pole o numerze n */

/*  Funkcja zwraca liczbê pól w wierszu ostatnio wczytanym 
    przez csv_getline.
    Zachowanie funkcji jest nieokre¶lone przed pierwszym
    wywo³aniem funkcji csv_getline.  */

extern int csv_nfield(void);  /* przeka¿ liczbê pól */

#endif
