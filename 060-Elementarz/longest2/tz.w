% --------------------------------------------------------------------
% This file is part of CWEB-NLS.
% It is distributed WITHOUT ANY WARRANTY, express or implied.
%
% Copyright (C) 2002 W{\l}odek Bzyl
% --------------------------------------------------------------------
\getCVSrevision$Revision: 1.2 $
\getCVSdate$Date: 2004/03/10 10:34:57 $
\getCVSsource$Source: /var/cvs/wyklady/JP1-L/14-Elementarz/longest1/tz.w,v $
% --------------------------------------------------------------------

% Strona tytu³owa --

\def\title{Tablice znakowe}
\def\topofcontents{\null\vfill
  \centerline{\titlefont tz.w --- przyk³ad programu opisowego}
  \vskip 15pt
  \centerline{(wersja \CVSrevision)}
  \vskip1in
  \vfill}
\def\botofcontents{\parskip=0pt \parindent=0pt
  \vskip 0pt plus 1filll
  Copyright \copyright\ 2003 W³odek Bzyl
  \bigskip
  Dokument ten zawiera przyk³ad z rozdzia³u 1.9 ksi±¿ki K\&R.
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
@f line x

\secpagedepth=2 % sekcje `@@*1' nie bêd± zaczynaæ siê od nowej strony

@ Najlepszym sposobem na nauczenie siê jêzyka \CEE/, jest samodzielne
pisanie programów w~tym jêzyku. Oto wersja opisowa programu
z~rozdzia³u 1.9 ksi±¿ki K\&R.

Najczê¶ciej u¿ywanymi tablicami w~jêzyku \CEE/ s± tablice znaków.
Aby pokazaæ sposób korzystania z~tych tablic oraz funkcje
manipuluj±ce nimi, napiszmy program, który czyta zbiór wierszy
i~wypisuje najd³u¿szy.

@c
@<W³±czane pliki nag³ówkowe@>@;
@<Deklaracje u¿ytych funkcji@>@;
int main() {
  @<Zmienne pomocnicze funkcji |main|@>@#
  @<Znajd¼ najd³u¿szy wiersz@>@/
  @<Wypisz najd³u¿szy wiersz@>@#
  return EXIT_SUCCESS;
}
@<Definicje u¿ytych funkcji@>@;

@ Ze powy¿szego schematu jasno wynika, ¿e program w~naturalny
sposób dzieli siê na czê¶ci. W~jednej z~nich jest czytany nowy
wiersz, w~innej sprawdza siê jego d³ugo¶æ, w~jeszcze innej
zachowuje wiersz, reszta za¶ steruje ca³ym procesem.

@<Znajd¼ najd³u¿szy wiersz@>=
  while (@<istnieje inny wiersz@>) {
    if (@<jest d³u¿szy od poprzednio najd³u¿szego@>) {
      @<zachowaj go@>@;
      @<zachowaj jego d³ugo¶æ@>@;
    }
  }

@ Problem da³ siê ³adnie podzieliæ na zadania, dobrze by³oby wiêc
napisaæ program w~ten sam sposób. Napiszmy zatem najpierw
oddzieln± funkcjê |getline|, pobieraj±c± z~wej¶cia nastêpny
wiersz. {\it Spróbujemy napisaæ j± tak, aby mog³a byæ u¿ywana
w~innych programach}. Jako minimum funkcja |getline| musi zwracaæ
sygna³ o~napotkaniu koñca pliku. Mo¿na zaakceptowaæ zero jako
sygna³ koñca pliku, nie jest on bowiem nigdy poprawn± d³ugo¶ci±
wiersza. Ka¿dy wiersz zawiera co najmniej jeden znak; nawet wiersz
sk³adaj±cy siê tylko ze znaku nowego wiersza ma d³ugo¶æ 1.

Powodem, dla którego w~deklaracji tablicy podaje siê jej rozmiar,
jest rezerwacja pamiêci. W~funkcji |getline| d³ugo¶æ tablicy |s|
nie jest potrzebna, poniewa¿ rozmiar tablicy jest okre¶lony
w~|main|. Instrukcja |return| s³u¿y funkcji |getline| do odes³ania
warto¶ci w~miejsce wywo³ania.

@<Deklaracje u¿ytych funkcji@>=
int getline(char s[], int lim);

@ Po stwierdzeniu, ¿e dany wiersz jest d³u¿szy od poprzednio
najd³u¿szego, nale¿y go gdzie¶ zapamiêtaæ. Sugeruje to stworzenie
funkcji |copy| przepisuj±cej nowy wiersz w~bezpieczne miejsce.

@<Deklaracje u¿ytych funkcji@>=
void copy(char to[], char from[]);

@ @<Zmienne pomocnicze funkcji |main|@>=
int  len; /* d³ugo¶æ bie¿±cego wiersza */
int max = 0; /* poprzednia maksymalna d³ugo¶æ */
char line[MAXLINE]; /* bie¿±cy wiersz z wej¶cia */
char longest[MAXLINE]; /* przechowywany maksymalny wiersz */

@ Je¶li |max=0|, to nic nie przeczytali¶my.

@<Wypisz najd³u¿szy wiersz@>=
if (max>0) {
  printf("%s",longest);
}

@ @<istnieje inny wiersz@>=
(len=getline(line,MAXLINE))>0

@ @<jest d³u¿szy od poprzednio najd³u¿szego@>=
len>max

@ @<zachowaj go@>=
copy(longest,line);

@ @<zachowaj jego d³ugo¶æ@>=
max=len;

@ Funkcja |getline| wstawia znak |'\0'| (znak |null|: nic, którego
warto¶ci± jest zero) na koniec tworzonej przez siebie tablicy, aby
zaznaczyæ koniec ci±gu znaków.

@<Definicje u¿ytych funkcji@>=
int getline(char s[], int lim) {
  int c, i;
  for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) {
    s[i]=c;
  }
  if (c=='\n') {
    s[i]=c;
    ++i;
  }
  s[i]='\0';
  return i;
}

@ @<Definicje u¿ytych funkcji@>=
void copy(char to[], char from[]) {
  int i;
  i=0;
  while ((to[i]=from[i])!='\0')
    ++i;
}

@ @<W³±czane pliki nag³ówkowe@>=
#include <stdio.h> /* definicja |printf| */
#include <stdlib.h> /* definicja |EXIT_SUCCESS| */
#define MAXLINE 1024 /* maksymalny rozmiar wiersza */

@* Skorowidz. 
Poni¿ej znajdziesz listê identyfikatorów u¿ytych w~programie 
\.{tz.w}. Liczba wskazuje na numer sekcji, w~której u¿yto identyfikatora,
a~liczba podkre¶lona --- numer sekcji w~której zdefiniowano identyfikator.
