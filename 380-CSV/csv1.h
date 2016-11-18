
/* csv1.h: pierwszy interfejs dla CSV */

/* Funkcja czyta wiersz z otwartego pliku wej¶ciowego f
    i dzieli go na pola. Funkcja zwraca liczbê znalezionych pól. */

extern int csv_getline(FILE *f);

/* Tablica wska¼ników do pól. */

extern char *csv_field[];
