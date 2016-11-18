#ifndef INCLUDED__MINIMAX_H
#define INCLUDED__MINIMAX_H

#include "eval-pos.h"
#include "game-repr.h"
#include "game-rules.h"
#include "config.h"

using namespace KIK;
      
// Ogólna funkcja FindBestMove zwracaj±ca najlepszy ruch, który mo¿e wykonaæ
// aktualny gracz (gracz, który musi wykonaæ nastêpny ruch).
//
// Funkcja ta jest niezale¿na od konkretnej reprezentacji gry -- wystarczy
// napisaæ w nowej przestrzeni nazw implementacjê regu³ gry i okre¶liæ
// reprezentacjê gry, by moæ j± zastosowaæ do dowolnej gry dwuosobowej

Move FindBestMove(State& state);

// Po ka¿dym wywo³aniu FindBestMove zmienna ta zawiera liczbê sytuacji na planszy gry,
// które przeanalizowano
extern int evaluated_positions;

#endif

