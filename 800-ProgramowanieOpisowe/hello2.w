% --------------------------------------------------------------------
% This file is part of CWEB-NLS.
% It is distributed WITHOUT ANY WARRANTY, express or implied.
%
% Copyright (C) 2004 W{\l}odek Bzyl
% --------------------------------------------------------------------
\getCVSrevision$Revision: 1.2 $
\getCVSdate$Date: 2004/11/22 11:13:16 $
\getCVSsource$Source: /var/cvs/wyklady/JP1-L/80-ProgramowanieOpisowe/hello2.w,v $
% --------------------------------------------------------------------

% Strona tytu³owa --

\def\title{HELLO 2}
\def\topofcontents{\null\vfill
  \centerline{\titlefont HELLO2.W}
  \vskip 15pt
  \centerline{(wersja \CVSrevision)}
  \vskip1in
  \vfill}
\def\botofcontents{\parskip=0pt \parindent=0pt
  \vskip 0pt plus 1filll
  Copyright \copyright\ 2002 W³odek Bzyl
  \bigskip
  Dokument ten zawiera najwa¿niejsze elementy programu opisowego
  ({\it literate program}).
  \bigskip
  \line{\tt\CVSsource\hfil\CVSdate}\par}

% -- albo data --

%\datethis

% Polskie litery w nazwach zmiennych
\noatl

\secpagedepth=2 % sekcje `@@*1' nie bêd± zaczynaæ siê od nowej strony

@* Wstêp.  
Najlepszym sposobem na nauczenie siê jêzyka \CEE/ jest samodzielne
pisanie programów w~tym jêzyku. Jest ju¿ zwyczajem, ¿e pierwszy
program ma za zadanie wypisaæ tekst:
$$\leftline{\hskip5em\tt hello, world}$$
Oto wersja opisowa ({\it literate\/}) takiego programu.

@ Na program \.{hello2} sk³adaj± siê:
\.{hello2.c} i \.{witaj.c} oraz plik nag³ówkowy \.{witaj.h}.

@c
@<W³±czane pliki nag³ówkowe i definicje zmiennych zewnêtrznych@>@#
int main()
{
  say_hello();
  return EXIT_SUCCESS;
}

@ @(witaj.c@>= 
@<W³±czane pliki nag³ówkowe i definicje zmiennych zewnêtrznych@>@;

void say_hello() {
  printf("hello, world\n");
}

@ @(witaj.h@>=
void say_hello();

@ @<W³±czane pliki nag³ówkowe i definicje zmiennych zewnêtrznych@>=
#include <stdio.h> /* definicja |printf| */
#include <stdlib.h> /* definicja |EXIT_SUCCESS| */
#include "witaj.h"

@* Skorowidz. 
Poni¿ej znajdziesz listê identyfikatorów u¿ytych w~programie 
\.{hello2.w}. Liczba wskazuje na numer sekcji, w~której u¿yto identyfikatora,
a~liczba podkre¶lona --- numer sekcji w~której zdefiniowano identyfikator.
