/* -*- mode: c -*- */

%module example

%{
/* miejsce na pliki nagłówkowe i deklaracje
   które mają być dopisane do pliku example_wrap.c  */
#include "example.h"
%}

/* lista rzeczy, które mają być dostępne w Rubym;
   w tym przykładzie udostępniamy wszystko z example.h  */

extern double foo;
extern int suma(int n, int m);
extern int silnia(int);
