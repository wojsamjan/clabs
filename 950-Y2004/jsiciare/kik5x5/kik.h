/*  
 *  File: kik.h
 *
 *  $Revision: 1.1.1.1 $
 *  $Date: 2004/01/24 10:39:05 $
 *
    Interfejs do gry w kó³ko i krzy¿yk.
 */

#ifndef KIK_INCLUDED
#define KIK_INCLUDED


#include "genlib.h"



/*  Sta³a ta okre¶la maksymaln± g³êboko¶æ rekurencji
    w poszukiwaniu najlepszego ruchu.
    W tej wersji programu przeprowadzamy analizê
    wszystkich ruchów. */

#define MaxDepth 4

/*  Rozmiar jednego boku planszy */

#define BoardSize 5

/*  Minimalna ilo¶æ punktów potrzebna do wygranej */

#define  WinnerResult 4

/*  Sta³e okre¶laj±ce system oceniania pozycji w grze. 
    Sta³e WinningPosition i LosingPosition s± przeciwnych
    znaków. Ich warto¶ci maj± okre¶laæ odpowiednio pewn±
    wygran± lub przegran±. W grze w której analizowane
    s± wszystkie mo¿liwe ruchy, nie s± potrzebne ¿adne
    inne po¶rednie oceny. Je¶li taka analiza nie jest
    mo¿liwa, to funkcja EvaluatePosition zwraca liczbê
    ca³kowit± miêdzy tymi dwoma skrajnymi warto¶ciami. */

#define WinningPosition  1000
#define NeutralPosition  0
#define LosingPosition  (-WinningPosition)

/*  Typ umo¿liwiaj±cy rozró¿nienie graczy. */

typedef enum { Human, Computer } playerT;

/*  Typ moveT powinien umo¿liwiæ zapamiêtanie pojedynczego
    ruchu w grze. 
    Dla gry w kó³ko i krzy¿yk, wystarczy zapamiêtaæ 
    pozycjê w której stawiamy `x' b±d¼ `o'. */

typedef int moveT;


/*  Sta³a ta okre¶la maksymaln± liczba ruchów.
    Korzystamy z niej alokuj±c, w danej pozycji, pamiêæ na 
    tablicê dopuszczalnych ruchów. */

#define MaxMoves  BoardSize*BoardSize


/*  Stan ka¿dej gry zapamiêtujemy w strukturze. Dla gry w kó³ko
    i krzy¿yk g³ównym elementem struktury jest tablica znakowa
    w której umieszczamy `x', `o', ` ', oznaczaj±c w ten sposób
    ruchy wykonane przez pierwszego i drugiego gracza oraz wolne
    miejsca. Chocia¿ tablica do gry jest dwuwymiarowa, to
    u¿ywamy tablicy jednowymiarowej, tak aby indeksy odpowiada³y
    numerom u¿ywanym przez graczy:

         1 | 2 | 3
        ---|---|---
         4 | 5 | 6
        ---|---|---
         7 | 8 | 9

    Zwróæmy uwage, ¿e element o indeksie 0 nie jest u¿ywany.
    Dodatkowo w strukturze zapamiêtujemy, kto nastêpny ma wykonaæ
    ruch. Dla gry w kó³ko i krzy¿yk wygodnie jest dodatkowo 
    pamiêtaæ liczbê wykonanych ruchów. Umo¿liwia to szybkie
    sprawdzenie, czy s± jeszcze wolne miejsca.
*/

typedef struct {
  char board[MaxMoves+1];
  playerT whoseTurn;
  int turnsTaken;
} *stateT;


/*  Sta³a ta wskazuje, kto ma pierwszy ruch. */

#define FirstPlayer Computer

/*  T± funkcj± zaczynamy now± grê. Zwraca ona stan pocz±tkowy
    gry. */

stateT NewGame(void);

/*  Funkcja zmienia stan gry wykonuj±c podany ruch. */

void MakeMove(stateT state, moveT move);

/*  Funkcja zwraca TRUE je¶li state wskazuje na koniec gry. */

int GameIsOver(stateT state);

/*  Funkcja zwracaj±ca w podanym stanie czyj jest ruch. */

playerT WhoseTurn(stateT state);

/*  Funkcja zmienia stan gry ,,odwo³uj±c'' podany ruch. */

void RetractMove(stateT state, moveT move);

/*  Funkcja zwraca TRUE je¶li podany gracz wygra³ grê. */

int CheckForWin(stateT state, playerT player);

/*  Funkcja zwraca warto¶æ wskazuj±ca czyj jest nastêpny ruch. */

playerT Opponent(playerT player);

#endif
