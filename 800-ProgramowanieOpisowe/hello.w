% --------------------------------------------------------------------
% This file is part of CWEB-NLS.
% It is distributed WITHOUT ANY WARRANTY, express or implied.
%
% Copyright (C) 2002 W{\l}odek Bzyl
% --------------------------------------------------------------------
\getCVSrevision$Revision: 1.1 $
\getCVSdate$Date: 2004/09/30 11:26:56 $
\getCVSsource$Source: /var/cvs/wyklady/JP1-L/80-ProgramowanieOpisowe/hello.w,v $
% --------------------------------------------------------------------

% Strona tytu³owa --

\def\title{HELLO}
\def\topofcontents{\null\vfill
  \centerline{\titlefont HELLO.W --- SZABLON PROGRAMU OPISOWEGO}
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
@l b1 xa
@l e6 xc
@l ea xe
@l b3 xl
@l f1 xn
@l f3 xo
@l b6 xs
@l bc xx
@l bf xz
@l a1 xA
@l c6 xC
@l ca xE
@l a3 xL
@l d1 xN
@l d3 xO
@l a6 xS
@l ac xX
@l af xZ

\secpagedepth=2 % sekcje `@@*1' nie bêd± zaczynaæ siê od nowej strony

@* Wstêp.  
Najlepszym sposobem na nauczenie siê jêzyka \CEE/ jest samodzielne
pisanie programów w~tym jêzyku. Jest ju¿ zwyczajem, ¿e pierwszy
program ma za zadanie wypisaæ tekst:
$$\leftline{\hskip5em\tt hello, world}$$
Oto wersja opisowa ({\it literate\/}) takiego programu.

@ Program \.{hello} sk³ada siê z~jednej funkcji o~nazwie
|main|. Nazwa ta ma specjalne znaczenie w~ka¿dym programie napisanym
w~jêzyku \CEE/. Ka¿dy program rozpoczyna dzia³anie od pocz±tku funkcji
|main|.

@c
@<W³±czane pliki nag³ówkowe i definicje zmiennych zewnêtrznych@>@#
int main()
{
  @<Wypisz przywitanie@>@;
  return EXIT_SUCCESS;
}

@ Ci±g znaków ujêty w~cudzys³owy nazywamy {\it napisem}.  Napis |"\n"|
reprezentuje znak nowego wiersza. Powoduje on przerwanie wypisywania
napisu w~bie¿±cym wierszu.  Wypisywanie zostanie wznowione od pocz±tku
nastêpnego wiersza.

@<Wypisz przywitanie@>= 
printf("hello, world\n");

@ Do wypisania napisu |"hello, world\n"| na standardowym wyj¶ciu u¿yto
funkcji |printf|.  Poni¿ej zlecamy kompilatorowi do³±czenie zawarto¶ci
pliku nag³ówkowego \.{stdio.h} do tekstu programu.  Plik ten zawiera
definicje standardowych funkcji wej¶cia/wyj¶cia (I/O), w~tym deklaracjê
funkcji |printf|.

@<W³±czane pliki nag³ówkowe i definicje zmiennych zewnêtrznych@>=
#include <stdio.h> /* definicja |printf| */
#include <stdlib.h> /* definicja |EXIT_SUCCESS| */

@ Drugim (i~ostatnim) do³±czanym plikiem nag³ówkowym jest \.{config.h}.

@(config.h@>=
#define VERSION "0.0.0 (alpha)"

@ Numer wersji tego programu umie¶cimy w~kodzie jako warto¶æ zmiennej
|version|. W~ten sposób bêdziemy mogli odró¿niæ program \.{hello},
który powstanie po przet³umaczeniu tego programu przy pomocy polecenia:
$$\leftline{\hskip5em\tt ct hello.w ; cc hello.c -o hello}$$
od innych programów o~tej samie nazwie.

@<W³±czane pliki nag³ówkowe i definicje zmiennych zewnêtrznych@>=
#include "config.h"
char version[] = VERSION;

@* Skorowidz. 
Poni¿ej znajdziesz listê identyfikatorów u¿ytych w~programie 
\.{hello.w}. Liczba wskazuje na numer sekcji, w~której u¿yto identyfikatora,
a~liczba podkre¶lona --- numer sekcji w~której zdefiniowano identyfikator.
