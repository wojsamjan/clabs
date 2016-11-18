% ------------------------------------------------------------------------
% This file is part of CWEB-NLS.
% It is distributed WITHOUT ANY WARRANTY, express or implied.
%
% Copyright (C) 2002 W{\l}odek Bzyl
% ------------------------------------------------------------------------
\getCVSrevision$Revision: 1.1 $
\getCVSdate$Date: 2004/09/30 11:26:56 $
\getCVSsource$Source: /var/cvs/wyklady/JP1-L/80-ProgramowanieOpisowe/sample.w,v $
% ------------------------------------------------------------------------

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

% Do not insert discretionary break in the middle of the string
%\def\){\discretionary{\hbox{\tentex\BS}}{}{}}
\def\){}

\def\floor#1{\lfloor#1\rfloor}
\def\dts{\mathinner{\ldotp\ldotp}}

% Strona tytu³owa --

\def\title{SAMPLE}
\def\topofcontents{\null\vfill
  \centerline{\titlefont PRÓBKA LOSOWA}
  \bigskip
  \centerline{\titlefont przyk³ad programu opisowego}
  \bigskip
  \centerline{(wersja \CVSrevision)}
  \vskip1in
  \vfill}
\def\botofcontents{\parskip=0pt \parindent=0pt
  \vfill
  Copyright \copyright\ 2002 W³odek Bzyl
  \bigskip
  Program ten generuje ci±g przypadkowych liczb naturalnych
  uporz±dkowanych rosn±co. Jest to wersja programu, 
  który po raz pierwszy pojawi³ siê w czasopi¶mie CACM w 1984 roku.
  \bigskip
  \line{\tt\CVSsource\hfil\CVSdate}\par}

@* Wstêp.
Program ten jest jednym z~rozwi±zañ nastêpuj±cego problemu:
\medskip
{\narrower\narrower
\noindent Na wej¶ciu dane s± dwie liczby naturalne $M$ i~$N$ takie,
¿e $M\xle N$. Na wyj¶ciu otrzymujemy $M$-elementowy, rosn±cy ci±g 
losowo wybranych liczb z~przedzia³u $[1\dts N]$.\par}
\medskip\noindent
Problem ten wraz z~rozwi±zaniem pojawi³ siê w~kolumnie ,,Programming
Pearls'' [CACM 1984]. Wed³ug D.~E. Knutha, autora rozwi±zania,
poni¿sze podej¶cie prowadzi do najefektywniejszego programu, gdy |M|
jest do¶æ du¿e i~jednocze¶nie ma³e wzglêdem |N|.
\medskip
Program ten mo¿na wykorzystaæ do generowania ,,szóstek'' w~{\sc
TOTO\=LOTKA}. Liczby do zaznaczenia na kuponie otrzymamy uruchamiaj±c
go w~nastêpuj±cy sposób:
\.{sample 6 49}.
\medskip
Wygenerowany ci±g liczb losowych zale¿y od liczby sekund, które
up³ynê³y od dnia 1~stycznia 1970 roku. I~tak, po uruchomieniu programu
dnia 24~wrze¶nia 1996 roku o~godzinie 13:05:53 (czas podany z~zegara
komputera), zosta³y wygenerowane nastêpuj±ce liczby:
\.{5 19 24 29 30 31}.
@^Knuth D.~E.@>
@^CACM@>
@^TOTO\=LOTEK@>

@ Zmienne |M| i~|N| to dane programu, opisane powy¿ej.  
Oto ich deklaracje.

@d  M_max 1001 /* maksymalna wielko¶æ |M| dozwolona w tym programie */

@<Zmienne globalne@>=
int M; /* liczba elementów w~próbce */
int N; /* losujemy liczby z przedzia³u $[1,N]$ */

@ Funkcje generuj±ce liczby losowe s± zadeklarowane w~pliku
\.{<stdlib.h>}. Tam te¿ zdefiniowano sta³± |RAND_MAX|.  
Do inicjalizacji generatora liczb losowych wykorzystamy
liczbê sekund zwracan± przez funkcjê |time|.

@c
#include <stdio.h>
#include <stdlib.h> /* deklaracje funkcji |exit|, |rand| i |srand| */
#include <time.h> /* deklaracja funkcji |time| */

@ Bêdziemy te¿ potrzebowaæ funkcji |liczba_losowa(i)| wybieraj±cej losowo
liczbê z~przedzia³u $[1\dts i]$. Strona podrêcznika dotycz±ca funkcji
|rand| zaleca aby u¿yæ poni¿szego wyra¿enia.

@c
unsigned int
liczba_losowa(i)
unsigned int i;
{
  return 1+(unsigned int)((float) i*rand()/(RAND_MAX+1.0));
}

@ @<Zainicjalizuj generator liczb losowych@>=
srand ((unsigned int) time((time_t) NULL));

@* Ogólny zarys programu.  Po wczytaniu liczb |M| i~|N| z~linii
poleceñ i~inicjalizacji generatora liczb losowych, generujemy 
kolejno elementy ci±gu w pêtli |while|.

@c
@<Zmienne globalne@>@;
int main(argc,argv)
  int argc; /* liczba argumentów w linii poleceñ */
  char *argv[]; /* argumenty  */
{
  @<Wczytaj warto¶ci |M| i |N| z linii poleceñ@>@;
  @<Zainicjalizuj generator liczb losowych@>@;
  @#
  @<Zacznij od zbioru pustego |S|@>@;
  liczba_elementów=0;
  while (liczba_elementów<M) {
    t=liczba_losowa(N);
    @<Je¶li |t| nie nale¿y do |S|, 
      to wstaw |t| i zwiêksz |liczbê_elementów|@>@;
  }
  @<Wypisz elementy |S| w porz±dku rosn±cym@>@;
  @#
  return EXIT_SUCCESS;
}

@ W schemacie opisanym powy¿ej pojawi³o siê kilka nowych zmiennych,
zadeklarujmy je teraz.
Reprezentacja zbioru |S| zostanie wprowadzona w~sekcji 11.

@<Zmienne globalne@>=
unsigned int liczba_elementów; /* liczba elementów zbioru |S| */
unsigned int t; /* nowy kandydat na element zbioru |S| */

@ @<Wczytaj warto¶ci |M| i |N| z linii poleceñ@>=
switch (argc) {
case 3:
  if (sscanf((char *) argv[1], "%d", &M)==1 &&
      sscanf((char *) argv[2], "%d", &N)==1) break;
default: wypisz_sposób_u¿ycia:
  fprintf(stderr, "U¿ycie: %s M N\n\
  gdzie M nale¿y do przedzia³u [1..N] i 1<=N<=%d\n",*argv,M_max);
  exit(-1);
}
@<Sprawd¼ poprawno¶æ danych wej¶ciowych@>

@ @<Sprawd¼ poprawno¶æ danych wej¶ciowych@>=
if (N<1 || M<1 || M>N || M>M_max || N>M_max) {
  fprintf(stderr,"! Nale¿y podaæ liczby M, N takie, ¿e M<=N.\n");
  goto wypisz_sposób_u¿ycia;
}

@ @<Zacznij od zbioru pustego |S|@>=
H_max=2*M-1;
alpha=(2.0*M)/N;
for(h=0;h<=H_max;h++) hash[h]=0;

@* Uporz±dkowane tablice rozproszone.
Kluczowym pomys³em prowadz±cym do sprawnie dzia³aj±cego programu jest
tworzenie zbioru |S| w~taki sposób, aby jego elementy mo¿na by³o ³atwo
i szybko uporz±dkowaæ. Jak zobaczymy, metoda ,,uporz±dkowanych tablic
rozproszonych'' [Amble i Knuth, {\it The Computer Journal} {\bf 17},
135--142] idealnie nadaje siê do tego zadania.
@^uporz±dkowane tablice rozproszone@>
@^Amble@>
@^Knuth D.~E.@>
\medskip
Tablice rozproszone posiadaj± nastêpuj±c± w³asno¶æ:
{\it Elementy uporz±dkowanej tablicy rozproszonej nie zale¿±
od kolejno¶ci w~której by³y wstawiane}. Dlatego uporz±dkowana
tablica rozproszona stanowi ,,kanoniczn±'' reprezentacjê zbioru
jej elementów.

Zbiór |S| bêdzie reprezentowany przez tablicê sk³adaj±c± siê
z~|2M| liczb ca³kowitych.

@<Zmienne globalne@>=
unsigned int hash[2*M_max]; /* uporz±dkowana tablica rozproszona */
unsigned int h; /* indeks w |hash| */
unsigned int H_max; /* maksymalna liczba elementów do wstawienia w~|hash| */
float alpha; /* $\hbox{rozmiar tablicy}/N$ */

@ Tutaj zajmiemy siê umieszczeniem elementu |t| w~tablicy
rozproszonej.  W~tym celu u¿yjemy funkcji mieszaj±cej obliczaj±cej
adres |h| wed³ug wzoru:
$$
h=\floor{2M(t-1)/N}.
$$
Zauwa¿my, ¿e jest to funkcja rosn±ca wzglêdem |t| o~prawie jednostajnym
rozk³adzie w~przedziale $0\xle h<2M$.

@<Je¶li |t| nie nale¿y do |S|, to wstaw |t| i zwiêksz |liczbê_elementów|@>=
h=(int)alpha*(t-1);@/
while (hash[h]>t) if (h==0) h=H_max; @+else h--;
if (hash[h]<t) { /* |t| nie wystêpuje w |S| */
  liczba_elementów++;
  @<Wstaw |t| w uporz±dkowan± tablicê rozproszon±@>
}

@ Najwa¿niejsz± czê¶æ algorytmu stanowi metoda wstawiania elementu
do tablicy rozproszonej. Nowy element |t| jest wstawiany w~miejsce
poprzedniego elementu $t_1<t$, który zostanie wstawiony w~miejsce
$t_2<t_1$ itd., a¿ do znalezienia wolnego miejsca.

@<Wstaw |t| w uporz±dkowan± tablicê rozproszon±@>=
while (hash[h]>0) {
   t_1=hash[h]; /* mamy $0<t_1<t$ */
   hash[h]=t;
   t=t_1;
   do {
     if (h==0) h=H_max; @+else h--;
   } while (hash[h]>=t);
}
hash[h]=t;

@ @<Zmienne globalne@>=
unsigned int t_1; /* przesuwany element tablicy */

@* Sortowanie w czasie liniowym.  
Kulminacyjnym fragmentem tego programu jest mo¿liwo¶æ prostego
odczytania w porz±dku rosn±cym elementów z~tablicy rozproszonej.
Dlaczego jest to mo¿liwe? Jak to powiedziano, ostateczny
stan tablicy nie zale¿y od kolejno¶ci, w~której wstawiano elementy.
Poniewa¿ u¿ywamy monotonicznej funkcji mieszaj±cej,
³atwo mo¿na sobie wyobraziæ, jak tablica siê zmienia w~przypadku
wstawiania elementów od najwiêkszego do najmniejszego.

Przyjmijmy, ¿e niezerowe elementy w~tablicy |hash|, to
$T_1<\cdots<T_M$. Je¶li $k$ z~nich, w~trakcie wstawiania,
przesuniêto z pocz±tku tablicy na jej koniec (tj. kiedy |h|
zmienia³o warto¶æ z |0| na |H_max| $k$ razy), to |hash[0]| bêdzie
zawieraæ zero (w~tym przypadku $k$ te¿ musi byæ równe zero), albo
bêdzie zawieraæ $T_{k+1}$. W~tym przypadku, elementy
$T_{k+1}<\cdots<T_M$ i~$T_1<\cdots<T_k$ pojawi± siê w tablicy
uporz±dkowane od lewej do prawej. Dlatego wstawione elementy mo¿na
wypisaæ w~porz±dku rosn±cym w~wyniku dwukrotnego przejrzenia
tablicy!

@d wypisz_element printf("%u ", hash[h])
@d wypisz_nl printf("\n")

@<Wypisz elementy |S| w porz±dku rosn±cym@>=
if (hash[0]==0) { /* nie by³o przesuniêcia na pozycjê |H_max| */
  for (h=1; h<=H_max; h++)
    if (hash[h]>0) wypisz_element; }
else { /* by³o przesuniêcie na pozycjê |H_max| */
  for (h=1; h<=H_max; h++)
    if (hash[h]>0) if (hash[h]<hash[0]) wypisz_element;
  for (h=0; h<=H_max; h++)
    if (hash[h]>=hash[0]) wypisz_element;
}
wypisz_nl;

@* Skorowidz. 
   Poni¿ej znajdziesz listê identyfikatorów u¿ytych w~programie 
\.{hello.w}. Liczba wskazuje na numer sekcji, w~której u¿yto identyfikatora,
a~liczba podkre¶lona --- numer sekcji w~której zdefiniowano identyfikator.
