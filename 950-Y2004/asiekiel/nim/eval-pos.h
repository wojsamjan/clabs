#ifndef INCLUDED__EVAL_POS_H
#define INCLUDED__EVAL_POS_H

#include "game-repr.h"

namespace KIK {

      // Oceny ruchów -- wygrywaj±ca i przegrywaj±ca
      const int WinningPosition = 100000;
      const int LosingPosition = -WinningPosition;

      // Oceñ dan± pozycjê na planszy
      int EvaluateStaticPosition(const GameBoard& board);

}

#endif

