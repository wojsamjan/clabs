#ifndef main_included
#define main_included

#include<gtk/gtk.h>

typedef enum { Computer, Human } stateT;
typedef struct {
    int nr_stosu, liczba;
} moveT;

extern int stos[3 + 1];
extern int dane[5];
extern GtkWidget *drawing_area;

GtkWidget *spinner5;
GtkWidget *spinner6;

moveT move;

void MakeMove(moveT move);

#endif
